/*
  This file is part of libkdepim.

  SPDX-FileCopyrightText: 2002 Helge Deller <deller@gmx.de>
  SPDX-FileCopyrightText: 2002 Lubos Lunak <llunak@suse.cz>
  SPDX-FileCopyrightText: 2001, 2003 Carsten Pfeiffer <pfeiffer@kde.org>
  SPDX-FileCopyrightText: 2001 Waldo Bastian <bastian@kde.org>
  SPDX-FileCopyrightText: 2004 Daniel Molkentin <danimo@klaralvdalens-datakonsult.se>
  SPDX-FileCopyrightText: 2004 Karl-Heinz Zimmer <khz@klaralvdalens-datakonsult.se>
  SPDX-FileCopyrightText: 2017-2024 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "addresseelineedit.h"
using namespace Qt::Literals::StringLiterals;

#include "addresseelineedit_p.h"
#include "addresseelineeditmanager.h"
#include "addresseelineeditutil.h"
#include "addressline/recentaddress/recentaddresses.h"
#include <KLDAPCore/LdapClientSearch>

#include <KContacts/VCardConverter>

#include <Akonadi/Job>
#include <KConfigGroup>
#include <QUrl>

#include <Akonadi/ContactGroupExpandJob>
#include <Akonadi/ContactGroupSearchJob>
#include <KColorScheme>
#include <KContacts/ContactGroupTool>
#include <KEmailAddress>
#include <KIO/StoredTransferJob>
#include <KJobWidgets>

#include "pimcommonakonadi_debug.h"
#include <KCodecs>
#include <KCompletionBox>
#include <KLocalizedString>
#include <KStandardShortcut>

#include "addressline/completionconfiguredialog/completionconfiguredialog.h"
#include <Akonadi/ContactGroupExpandJob>
#include <KContacts/VCardDrag>
#include <KMessageBox>
#include <KSharedConfig>
#include <QApplication>
#include <QBuffer>
#include <QClipboard>
#include <QDropEvent>
#include <QEvent>
#include <QKeyEvent>
#include <QMenu>
#include <QMimeData>
#include <QMouseEvent>
#include <QObject>

using namespace PimCommon;

inline bool itemIsHeader(const QListWidgetItem *item)
{
    return item && !item->text().startsWith("     "_L1);
}

// needs to be unique, but the actual name doesn't matter much
static QString newLineEditObjectName()
{
    static int s_count = 0;
    QString name(QStringLiteral("KPIM::AddresseeLineEdit"));
    if (s_count++) {
        name += QLatin1Char('-');
        name += QString::number(s_count);
    }
    return name;
}

AddresseeLineEdit::AddresseeLineEdit(QWidget *parent, bool enableCompletion)
    : KLineEdit(parent)
    , d(new AddresseeLineEditPrivate(this, enableCompletion))
{
    setObjectName(newLineEditObjectName());
    setPlaceholderText(QString());

    d->init();
}

AddresseeLineEdit::~AddresseeLineEdit()
{
    delete d;
}

void AddresseeLineEdit::setFont(const QFont &font)
{
    KLineEdit::setFont(font);

    if (d->useCompletion()) {
        completionBox()->setFont(font);
    }
}

void AddresseeLineEdit::setIcon(const QIcon &icon, const QString &tooltip)
{
    d->setIcon(icon, tooltip);
}

bool AddresseeLineEdit::expandIntern() const
{
    return d->expandIntern();
}

void AddresseeLineEdit::setExpandIntern(bool expand)
{
    d->setExpandIntern(expand);
}

void AddresseeLineEdit::setEnableBalooSearch(bool enable)
{
    d->setEnableBalooSearch(enable);
}

bool AddresseeLineEdit::enableBalooSearch() const
{
    return d->enableAkonadiSearch();
}

void AddresseeLineEdit::setEnableAkonadiSearch(bool enable)
{
    d->setEnableAkonadiSearch(enable);
}

bool AddresseeLineEdit::enableAkonadiSearch() const
{
    return d->enableAkonadiSearch();
}

void AddresseeLineEdit::allowSemicolonAsSeparator(bool useSemicolonAsSeparator)
{
    d->setUseSemicolonAsSeparator(useSemicolonAsSeparator);
}

bool AddresseeLineEdit::showRecentAddresses() const
{
    return d->showRecentAddresses();
}

void AddresseeLineEdit::setShowRecentAddresses(bool b)
{
    d->setShowRecentAddresses(b);
}

void AddresseeLineEdit::keyPressEvent(QKeyEvent *event)
{
    bool accept = false;

    const int key = event->key() | event->modifiers();

    if (KStandardShortcut::shortcut(KStandardShortcut::SubstringCompletion).contains(key)) {
        // TODO: add LDAP substring lookup, when it becomes available in KPIM::LDAPSearch
        d->updateSearchString();
        d->startSearches();
        d->doCompletion(true);
        accept = true;
    } else if (KStandardShortcut::shortcut(KStandardShortcut::TextCompletion).contains(key)) {
        const int len = text().length();

        if (len == cursorPosition()) { // at End?
            d->updateSearchString();
            d->startSearches();
            d->doCompletion(true);
            accept = true;
        }
    }

    const QString oldContent = text();
    if (!accept) {
        KLineEdit::keyPressEvent(event);
    }

    // if the text didn't change (eg. because a cursor navigation key was pressed)
    // we don't need to trigger a new search
    if (oldContent == text()) {
        return;
    }

    if (event->isAccepted()) {
        d->updateSearchString();

        QString searchString(d->searchString());
        // LDAP does not know about our string manipulation, remove it
        if (d->searchExtended()) {
            searchString = d->searchString().mid(1);
        }

        d->restartTime(searchString);
    }
}

void AddresseeLineEdit::insert(const QString &t)
{
    if (!d->smartPaste()) {
        KLineEdit::insert(t);
        return;
    }

    QString newText = t.trimmed();
    if (newText.isEmpty()) {
        return;
    }

    newText = PimCommon::AddresseeLineEditUtil::adaptPasteMails(newText);

    QString contents = text();
    int pos = cursorPosition();

    if (hasSelectedText()) {
        // Cut away the selection.
        int start_sel = selectionStart();
        pos = start_sel;
        contents = contents.left(start_sel) + contents.mid(start_sel + selectedText().length());
    }

    int eot = contents.length();
    while ((eot > 0) && contents.at(eot - 1).isSpace()) {
        --eot;
    }
    if (eot == 0) {
        contents.clear();
    } else if (pos >= eot) {
        if (contents.at(eot - 1) == QLatin1Char(',')) {
            --eot;
        }
        contents.truncate(eot);
        contents += QStringLiteral(", ");
        pos = eot + 2;
    }

    contents = contents.left(pos) + newText + contents.mid(pos);
    setText(contents);
    setModified(true);
    setCursorPosition(pos + newText.length());
}

void AddresseeLineEdit::setText(const QString &text)
{
    const int cursorPos = cursorPosition();
    KLineEdit::setText(text.trimmed());
    setCursorPosition(cursorPos);
}

void AddresseeLineEdit::paste()
{
    if (d->useCompletion()) {
        d->setSmartPaste(true);
    }

    KLineEdit::paste();
    d->setSmartPaste(false);
}

void AddresseeLineEdit::mouseReleaseEvent(QMouseEvent *event)
{
    // reimplemented from QLineEdit::mouseReleaseEvent()
    if (d->useCompletion() && QApplication::clipboard()->supportsSelection() && !isReadOnly() && event->button() == Qt::MiddleButton) {
        d->setSmartPaste(true);
    }

    KLineEdit::mouseReleaseEvent(event);
    d->setSmartPaste(false);
}

void AddresseeLineEdit::dropEvent(QDropEvent *event)
{
    const QMimeData *md = event->mimeData();
    // Case one: The user dropped a text/directory (i.e. vcard), so decode its
    //           contents
    if (KContacts::VCardDrag::canDecode(md)) {
        KContacts::Addressee::List list;
        KContacts::VCardDrag::fromMimeData(md, list);

        for (const KContacts::Addressee &addr : std::as_const(list)) {
            insertEmails(addr.emails());
        }
    }
    // Case two: The user dropped a list or Urls.
    // Iterate over that list. For mailto: Urls, just add the addressee to the list,
    // and for other Urls, download the Url and assume it points to a vCard
    else if (md->hasUrls()) {
        const QList<QUrl> urls = md->urls();
        KContacts::Addressee::List list;

        for (const QUrl &url : urls) {
            // First, let's deal with mailto Urls. The path() part contains the
            // email-address.
            if (url.scheme() == "mailto"_L1) {
                KContacts::Addressee addressee;
                KContacts::Email email(KEmailAddress::decodeMailtoUrl(url));
                email.setPreferred(true);
                addressee.addEmail(email);
                list += addressee;
            } else { // Otherwise, download the vCard to which the Url points
                KContacts::VCardConverter converter;
                auto job = KIO::storedGet(url);
                KJobWidgets::setWindow(job, parentWidget());
                if (job->exec()) {
                    QByteArray data = job->data();
                    list += converter.parseVCards(data);

                    if (list.isEmpty()) { // try to parse a contact group
                        KContacts::ContactGroup group;
                        QBuffer dataStream(&data);
                        dataStream.open(QIODevice::ReadOnly);
                        QString error;
                        if (KContacts::ContactGroupTool::convertFromXml(&dataStream, group, &error)) {
                            auto expandJob = new Akonadi::ContactGroupExpandJob(group);
                            connect(expandJob, &Akonadi::ContactGroupExpandJob::result, this, &AddresseeLineEdit::groupExpandResult);
                            expandJob->start();
                        } else {
                            qCWarning(PIMCOMMONAKONADI_LOG) << "Error during converting contactgroup " << error;
                        }
                    }
                } else {
                    const QString caption(i18n("vCard Import Failed"));
                    const QString text = i18n("<qt>Unable to access <b>%1</b>.</qt>", url.url());
                    KMessageBox::error(parentWidget(), text, caption);
                }
            }
        }

        // Now, let the user choose which addressee to add.
        for (const KContacts::Addressee &addressee : std::as_const(list)) {
            insertEmails(addressee.emails());
        }
    }
    // Case three: Let AddresseeLineEdit deal with the rest
    else {
        if (!isReadOnly()) {
            const QList<QUrl> uriList = event->mimeData()->urls();
            if (!uriList.isEmpty()) {
                QString contents = text();
                // remove trailing white space and comma
                int eot = contents.length();
                while ((eot > 0) && contents.at(eot - 1).isSpace()) {
                    --eot;
                }
                if (eot == 0) {
                    contents.clear();
                } else if (contents.at(eot - 1) == QLatin1Char(',')) {
                    --eot;
                    contents.truncate(eot);
                }
                bool mailtoURL = false;
                // append the mailto URLs
                for (const QUrl &url : uriList) {
                    if (url.scheme() == "mailto"_L1) {
                        mailtoURL = true;
                        QString address;
                        address = QUrl::fromPercentEncoding(url.path().toLatin1());
                        address = KCodecs::decodeRFC2047String(address);
                        if (!contents.isEmpty()) {
                            contents.append(", "_L1);
                        }
                        contents.append(address);
                    }
                }
                if (mailtoURL) {
                    setText(contents);
                    setModified(true);
                    return;
                }
            } else {
                // Let's see if this drop contains a comma separated list of emails
                if (md->hasText()) {
                    const QString dropData = md->text();
                    const QStringList addrs = KEmailAddress::splitAddressList(dropData);
                    if (!addrs.isEmpty()) {
                        if (addrs.count() == 1) {
                            QUrl url(dropData);
                            if (url.scheme() == "mailto"_L1) {
                                KContacts::Addressee addressee;
                                KContacts::Email email(KEmailAddress::decodeMailtoUrl(url));
                                email.setPreferred(true);
                                addressee.addEmail(email);
                                insertEmails(addressee.emails());
                            } else {
                                setText(KEmailAddress::normalizeAddressesAndDecodeIdn(dropData));
                            }
                        } else {
                            setText(KEmailAddress::normalizeAddressesAndDecodeIdn(dropData));
                        }
                        setModified(true);
                        return;
                    }
                }
            }
        }

        if (d->useCompletion()) {
            d->setSmartPaste(true);
        }

        QLineEdit::dropEvent(event);
        d->setSmartPaste(false);
    }
}

void AddresseeLineEdit::groupExpandResult(KJob *job)
{
    auto expandJob = qobject_cast<Akonadi::ContactGroupExpandJob *>(job);

    if (!expandJob) {
        return;
    }

    const KContacts::Addressee::List contacts = expandJob->contacts();
    for (const KContacts::Addressee &addressee : contacts) {
        if (d->expandIntern() || text().trimmed().isEmpty()) {
            insertEmails({addressee.fullEmail()});
        } else {
            Q_EMIT addAddress(addressee.fullEmail());
        }
    }

    job->deleteLater();
}

void AddresseeLineEdit::insertEmails(const QStringList &emails)
{
    if (emails.empty()) {
        return;
    }

    QString contents = text();
    if (!contents.isEmpty()) {
        contents += QLatin1Char(',');
    }
    // only one address, don't need kpopup to choose
    if (emails.size() == 1) {
        setText(contents + emails.front());
        return;
    }
    // multiple emails, let the user choose one
    QMenu menu(this);
    menu.setTitle(i18n("Select email from contact"));
    menu.setObjectName("Addresschooser"_L1);
    for (const QString &email : emails) {
        menu.addAction(email);
    }
    const QAction *result = menu.exec(QCursor::pos());
    if (!result) {
        return;
    }
    setText(contents + KLocalizedString::removeAcceleratorMarker(result->text()));
}

void AddresseeLineEdit::cursorAtEnd()
{
    setCursorPosition(text().length());
}

void AddresseeLineEdit::enableCompletion(bool enable)
{
    d->setUseCompletion(enable);
}

bool AddresseeLineEdit::isCompletionEnabled() const
{
    return d->useCompletion();
}

void AddresseeLineEdit::addItem(const Akonadi::Item &item, int weight, int source)
{
    // Let Akonadi results always have a higher weight than baloo results
    if (item.hasPayload<KContacts::Addressee>()) {
        addContact(item.payload<KContacts::Addressee>(), weight + 1, source);
    } else if (item.hasPayload<KContacts::ContactGroup>()) {
        addContactGroup(item.payload<KContacts::ContactGroup>(), weight + 1, source);
    }
}

void AddresseeLineEdit::addContactGroup(const KContacts::ContactGroup &group, int weight, int source)
{
    d->addCompletionItem(group.name(), weight, source);
}

void AddresseeLineEdit::addContact(const QStringList &emails, const KContacts::Addressee &addr, int weight, int source, QString append)
{
    int isPrefEmail = 1; // first in list is preferredEmail
    for (const QString &email : emails) {
        // TODO: highlight preferredEmail
        const QString givenName = addr.givenName();
        const QString familyName = addr.familyName();
        const QString nickName = addr.nickName();
        const QString fullEmail = addr.fullEmail(email);

        QString appendix;

        if (!append.isEmpty()) {
            appendix = QStringLiteral(" (%1)");
            append.replace(QLatin1Char('('), QStringLiteral("["));
            append.replace(QLatin1Char(')'), QStringLiteral("]"));
            appendix = appendix.arg(append);
        }

        // Prepare "givenName" + ' ' + "familyName"
        QString fullName = givenName;
        if (!familyName.isEmpty()) {
            if (!fullName.isEmpty()) {
                fullName += QLatin1Char(' ');
            }
            fullName += familyName;
        }

        // Finally, we can add the completion items
        if (!fullName.isEmpty()) {
            const QString address = KEmailAddress::normalizedAddress(fullName, email, QString());
            if (fullEmail != address) {
                // This happens when fullEmail contains a middle name, while our own fullName+email only has "first last".
                // Let's offer both, the fullEmail with 3 parts, looks a tad formal.
                d->addCompletionItem(address + appendix, weight + isPrefEmail, source);
            }
        }

        QStringList keyWords;
        if (!nickName.isEmpty()) {
            keyWords.append(nickName);
        }

        d->addCompletionItem(fullEmail + appendix, weight + isPrefEmail, source, &keyWords);

        isPrefEmail = 0;
    }
}

void AddresseeLineEdit::addContact(const KContacts::Addressee &addr, int weight, int source, const QString &append)
{
    const QStringList emails = AddresseeLineEditManager::self()->cleanupEmailList(addr.emails());
    if (emails.isEmpty()) {
        return;
    }
    addContact(emails, addr, weight, source, append);
}

void AddresseeLineEdit::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu *menu = createStandardContextMenu();
    if (menu) { // can be 0 on platforms with only a touch interface
        menu->exec(event->globalPos());
        delete menu;
    }
}

QMenu *AddresseeLineEdit::createStandardContextMenu()
{
    // disable modes not supported by KMailCompletion
    setCompletionModeDisabled(KCompletion::CompletionMan);
    setCompletionModeDisabled(KCompletion::CompletionPopupAuto);

    QMenu *menu = KLineEdit::createStandardContextMenu();
    if (!menu) {
        return nullptr;
    }
    if (d->useCompletion()) {
        auto showOU = new QAction(i18n("Show Organization Unit for LDAP results"), menu);
        showOU->setCheckable(true);
        showOU->setChecked(d->showOU());
        connect(showOU, &QAction::triggered, d, &AddresseeLineEditPrivate::slotShowOUChanged);
        menu->addAction(showOU);
    }
    if (isCompletionEnabled()) {
        menu->addSeparator();
        QAction *act = menu->addAction(i18n("Configure Completion..."));
        connect(act, &QAction::triggered, this, &AddresseeLineEdit::configureCompletion);
    }
    menu->addSeparator();
    QAction *act = menu->addAction(i18n("Automatically expand groups"));
    act->setCheckable(true);
    act->setChecked(d->autoGroupExpand());
    connect(act, &QAction::triggered, d, &AddresseeLineEditPrivate::slotToggleExpandGroups);

    if (!d->groupsIsEmpty()) {
        act = menu->addAction(i18n("Expand Groups..."));
        connect(act, &QAction::triggered, this, &AddresseeLineEdit::expandGroups);
    }
    return menu;
}

bool AddresseeLineEdit::canDeleteLineEdit() const
{
    return d->canDeleteLineEdit();
}

void AddresseeLineEdit::configureCompletion()
{
    d->setCanDeleteLineEdit(false);
    QScopedPointer<PimCommon::CompletionConfigureDialog> dlg(new PimCommon::CompletionConfigureDialog(this));
    dlg->setRecentAddresses(PimCommon::RecentAddresses::self(recentAddressConfig())->addresses());
    dlg->setLdapClientSearch(ldapSearch());
    dlg->setEmailBlackList(PimCommon::AddresseeLineEditManager::self()->balooBlackList());
    dlg->load();
    if (dlg->exec() && dlg) {
        if (dlg->recentAddressWasChanged()) {
            PimCommon::RecentAddresses::self(recentAddressConfig())->clear();
            dlg->storeAddresses(recentAddressConfig());
            loadContacts();
        }
        updateBalooBlackList();
        updateCompletionOrder();
    }
    d->setCanDeleteLineEdit(true);
}

void AddresseeLineEdit::loadContacts()
{
    const QString recentAddressGroupName = i18n("Recent Addresses");
    if (showRecentAddresses()) {
        const QStringList recent =
            AddresseeLineEditManager::self()->cleanupRecentAddressEmailList(PimCommon::RecentAddresses::self(recentAddressConfig())->addresses());
        QString name;
        QString emailString;

        KSharedConfig::Ptr config = KSharedConfig::openConfig(QStringLiteral("kpimcompletionorder"));
        KConfigGroup group(config, QStringLiteral("CompletionWeights"));
        const int weight = group.readEntry("Recent Addresses", 10);
        removeCompletionSource(recentAddressGroupName);
        const int idx = addCompletionSource(recentAddressGroupName, weight);

        for (const QString &recentAdr : recent) {
            KContacts::Addressee addr;
            KEmailAddress::extractEmailAddressAndName(recentAdr, emailString, name);
            if (emailString.isEmpty()) {
                continue;
            }
            name = KEmailAddress::quoteNameIfNecessary(name);
            if (!name.isEmpty() && (name[0] == QLatin1Char('"')) && (name[name.length() - 1] == QLatin1Char('"'))) {
                name.remove(0, 1);
                name.chop(1);
            }
            addr.setNameFromString(name);
            KContacts::Email email(emailString);
            email.setPreferred(true);
            addr.addEmail(email);
            addContact({emailString}, addr, weight, idx);
        }
    } else {
        removeCompletionSource(recentAddressGroupName);
    }
}

void AddresseeLineEdit::removeCompletionSource(const QString &source)
{
    d->removeCompletionSource(source);
}

int AddresseeLineEdit::addCompletionSource(const QString &source, int weight)
{
    return d->addCompletionSource(source, weight);
}

bool AddresseeLineEdit::eventFilter(QObject *object, QEvent *event)
{
    if (d->completionInitialized() && (object == completionBox() || completionBox()->findChild<QWidget *>(object->objectName()) == object)) {
        if (event->type() == QEvent::MouseButtonPress || event->type() == QEvent::MouseMove || event->type() == QEvent::MouseButtonRelease
            || event->type() == QEvent::MouseButtonDblClick) {
            const QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            // find list box item at the event position
            QListWidgetItem *item = completionBox()->itemAt(mouseEvent->pos());
            if (!item) {
                // In the case of a mouse move outside of the box we don't want
                // the parent to fuzzy select a header by mistake.
                const bool eat = event->type() == QEvent::MouseMove;
                return eat;
            }
            // avoid selection of headers on button press, or move or release while
            // a button is pressed
            const Qt::MouseButtons buttons = mouseEvent->buttons();
            if (event->type() == QEvent::MouseButtonPress || event->type() == QEvent::MouseButtonDblClick || buttons & Qt::LeftButton
                || buttons & Qt::MiddleButton || buttons & Qt::RightButton) {
                if (itemIsHeader(item)) {
                    return true; // eat the event, we don't want anything to happen
                } else {
                    // if we are not on one of the group heading, make sure the item
                    // below or above is selected, not the heading, inadvertedly, due
                    // to fuzzy auto-selection from QListBox
                    completionBox()->setCurrentItem(item);
                    item->setSelected(true);
                    if (event->type() == QEvent::MouseMove) {
                        return true; // avoid fuzzy selection behavior
                    }
                }
            }
        }
    }

    if ((object == this) && (event->type() == QEvent::ShortcutOverride)) {
        auto keyEvent = static_cast<QKeyEvent *>(event);
        if (keyEvent->key() == Qt::Key_Up || keyEvent->key() == Qt::Key_Down || keyEvent->key() == Qt::Key_Tab) {
            keyEvent->accept();
            return true;
        }
    }

    if ((object == this) && (event->type() == QEvent::KeyPress || event->type() == QEvent::KeyRelease) && completionBox()->isVisible()) {
        const QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        int currentIndex = completionBox()->currentRow();
        if (currentIndex < 0) {
            return true;
        }
        if (keyEvent->key() == Qt::Key_Up) {
            // qCDebug(PIMCOMMONAKONADI_LOG) <<"EVENTFILTER: Qt::Key_Up currentIndex=" << currentIndex;
            // figure out if the item we would be moving to is one we want
            // to ignore. If so, go one further
            const QListWidgetItem *itemAbove = completionBox()->item(currentIndex);
            if (itemAbove && itemIsHeader(itemAbove)) {
                // there is a header above is, check if there is even further up
                // and if so go one up, so it'll be selected
                if (currentIndex > 0 && completionBox()->item(currentIndex - 1)) {
                    // qCDebug(PIMCOMMONAKONADI_LOG) <<"EVENTFILTER: Qt::Key_Up -> skipping" << currentIndex - 1;
                    completionBox()->setCurrentRow(currentIndex - 1);
                    completionBox()->item(currentIndex - 1)->setSelected(true);
                } else if (currentIndex == 0) {
                    // nothing to skip to, let's stay where we are, but make sure the
                    // first header becomes visible, if we are the first real entry
                    completionBox()->scrollToItem(completionBox()->item(0));
                    QListWidgetItem *item = completionBox()->item(currentIndex);
                    if (item) {
                        if (itemIsHeader(item)) {
                            currentIndex++;
                            item = completionBox()->item(currentIndex);
                        }
                        completionBox()->setCurrentItem(item);
                        item->setSelected(true);
                    }
                }

                return true;
            }
        } else if (keyEvent->key() == Qt::Key_Down) {
            // same strategy for downwards
            // qCDebug(PIMCOMMONAKONADI_LOG) <<"EVENTFILTER: Qt::Key_Down. currentIndex=" << currentIndex;
            const QListWidgetItem *itemBelow = completionBox()->item(currentIndex);
            if (itemBelow && itemIsHeader(itemBelow)) {
                if (completionBox()->item(currentIndex + 1)) {
                    // qCDebug(PIMCOMMONAKONADI_LOG) <<"EVENTFILTER: Qt::Key_Down -> skipping" << currentIndex+1;
                    completionBox()->setCurrentRow(currentIndex + 1);
                    completionBox()->item(currentIndex + 1)->setSelected(true);
                } else {
                    // nothing to skip to, let's stay where we are
                    QListWidgetItem *item = completionBox()->item(currentIndex);
                    if (item) {
                        completionBox()->setCurrentItem(item);
                        item->setSelected(true);
                    }
                }

                return true;
            }
            // special case of the initial selection, which is unfortunately a header.
            // Setting it to selected tricks KCompletionBox into not treating is special
            // and selecting making it current, instead of the one below.
            QListWidgetItem *item = completionBox()->item(currentIndex);
            if (item && itemIsHeader(item)) {
                completionBox()->setCurrentItem(item);
                item->setSelected(true);
            }
        } else if (event->type() == QEvent::KeyRelease && (keyEvent->key() == Qt::Key_Tab || keyEvent->key() == Qt::Key_Backtab)) {
            /// first, find the header of the current section
            QListWidgetItem *myHeader = nullptr;
            int myHeaderIndex = -1;
            const int iterationStep = keyEvent->key() == Qt::Key_Tab ? 1 : -1;
            int index = qMin(qMax(currentIndex - iterationStep, 0), completionBox()->count() - 1);
            while (index >= 0) {
                if (itemIsHeader(completionBox()->item(index))) {
                    myHeader = completionBox()->item(index);
                    myHeaderIndex = index;
                    break;
                }

                index--;
            }
            Q_ASSERT(myHeader); // we should always be able to find a header

            // find the next header (searching backwards, for Qt::Key_Backtab)
            QListWidgetItem *nextHeader = nullptr;

            // when iterating forward, start at the currentindex, when backwards,
            // one up from our header, or at the end
            int j;
            if (keyEvent->key() == Qt::Key_Tab) {
                j = currentIndex;
            } else {
                index = myHeaderIndex;
                if (index == 0) {
                    j = completionBox()->count() - 1;
                } else {
                    j = (index - 1) % completionBox()->count();
                }
            }
            while ((nextHeader = completionBox()->item(j)) && nextHeader != myHeader) {
                if (itemIsHeader(nextHeader)) {
                    break;
                }
                j = (j + iterationStep) % completionBox()->count();
            }

            if (nextHeader && nextHeader != myHeader) {
                QListWidgetItem *item = completionBox()->item(j + 1);
                if (item && !itemIsHeader(item)) {
                    completionBox()->setCurrentItem(item);
                    item->setSelected(true);
                }
            }

            return true;
        }
    }

    return KLineEdit::eventFilter(object, event);
}

void AddresseeLineEdit::emitTextCompleted()
{
    Q_EMIT textCompleted();
}

void AddresseeLineEdit::callUserCancelled(const QString &str)
{
    userCancelled(str);
}

void AddresseeLineEdit::callSetCompletedText(const QString &text, bool marked)
{
    setCompletedText(text, marked);
}

void AddresseeLineEdit::callSetCompletedText(const QString &text)
{
    setCompletedText(text);
}

void AddresseeLineEdit::callSetUserSelection(bool b)
{
    setUserSelection(b);
}

void AddresseeLineEdit::updateBalooBlackList()
{
    d->updateBalooBlackList();
}

void AddresseeLineEdit::updateCompletionOrder()
{
    d->updateCompletionOrder();
}

KLDAPCore::LdapClientSearch *AddresseeLineEdit::ldapSearch() const
{
    return d->ldapSearch();
}

void AddresseeLineEdit::slotEditingFinished()
{
    const QList<KJob *> listJob = d->mightBeGroupJobs();
    for (KJob *job : listJob) {
        disconnect(job);
        job->deleteLater();
    }

    d->mightBeGroupJobsClear();
    d->groupsClear();

    if (!text().trimmed().isEmpty() && enableAkonadiSearch()) {
        const QStringList addresses = KEmailAddress::splitAddressList(text());
        for (const QString &address : addresses) {
            auto job = new Akonadi::ContactGroupSearchJob();
            connect(job, &Akonadi::ContactGroupSearchJob::result, this, &AddresseeLineEdit::slotGroupSearchResult);
            d->mightBeGroupJobsAdd(job);
            job->setQuery(Akonadi::ContactGroupSearchJob::Name, address);
        }
    }
}

void AddresseeLineEdit::slotGroupSearchResult(KJob *job)
{
    auto searchJob = qobject_cast<Akonadi::ContactGroupSearchJob *>(job);

    // Laurent I don't understand why Akonadi::ContactGroupSearchJob send two "result(...)" signal. For the moment
    // avoid to go in this method twice, until I understand it.
    if (!d->mightBeGroupJobs().contains(searchJob)) {
        return;
    }
    // Q_ASSERT(d->mMightBeGroupJobs.contains(searchJob));
    d->mightBeGroupJobsRemoveOne(searchJob);

    const KContacts::ContactGroup::List contactGroups = searchJob->contactGroups();
    if (contactGroups.isEmpty()) {
        return; // Nothing todo, probably a normal email address was entered
    }

    d->addGroups(contactGroups);
    searchJob->deleteLater();

    if (d->autoGroupExpand()) {
        expandGroups();
    }
}

void AddresseeLineEdit::expandGroups()
{
    QStringList addresses = KEmailAddress::splitAddressList(text());

    const KContacts::ContactGroup::List lstGroups = d->groups();
    for (const KContacts::ContactGroup &group : lstGroups) {
        auto expandJob = new Akonadi::ContactGroupExpandJob(group);
        connect(expandJob, &Akonadi::ContactGroupExpandJob::result, this, &AddresseeLineEdit::groupExpandResult);
        addresses.removeAll(group.name());
        expandJob->start();
    }
    setText(addresses.join(", "_L1));
    d->groupsClear();
}

void AddresseeLineEdit::setRecentAddressConfig(KConfig *config)
{
    d->setRecentAddressConfig(config);
}

KConfig *AddresseeLineEdit::recentAddressConfig() const
{
    return d->recentAddressConfig();
}

#include "moc_addresseelineedit.cpp"
