/*
 * This file is part of libkldap.
 *
 * SPDX-FileCopyrightText: 2002 Klarälvdalens Datakonsult AB
 * SPDX-FileContributor: Steffen Hansen <hansen@kde.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 */

#include "ldapsearchdialog.h"

#include <KLDAP/LdapClient>

#include <KLDAP/LdapClientSearchConfig>
#include <KLDAP/LdapSearchClientReadConfigServerJob>
#include <Libkdepim/LineEditCatchReturnKey>
#include <Libkdepim/ProgressIndicatorLabel>

#include <QApplication>
#include <QCheckBox>
#include <QClipboard>
#include <QCloseEvent>
#include <QFrame>
#include <QGridLayout>
#include <QGroupBox>
#include <QHeaderView>
#include <QLabel>
#include <QMenu>
#include <QPair>
#include <QPointer>
#include <QPushButton>
#include <QSortFilterProxyModel>
#include <QTableView>
#include <QVBoxLayout>

#include <KCMultiDialog>
#include <KConfig>
#include <KConfigGroup>
#include <KMessageBox>
#include <KPluginMetaData>
#include <QComboBox>
#include <QDialogButtonBox>
#include <QLineEdit>
#include <kldap/ldapobject.h>
#include <kldap/ldapserver.h>

#include <KConfigGroup>
#include <KGuiItem>
#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QLocale>

using namespace PimCommon;
static QString asUtf8(const QByteArray &val)
{
    if (val.isEmpty()) {
        return {};
    }

    const char *data = val.data();

    // QString::fromUtf8() bug workaround
    if (data[val.size() - 1] == '\0') {
        return QString::fromUtf8(data, val.size() - 1);
    } else {
        return QString::fromUtf8(data, val.size());
    }
}

static QString join(const KLDAP::LdapAttrValue &lst, const QString &sep)
{
    QString res;
    bool already = false;
    KLDAP::LdapAttrValue::ConstIterator end(lst.constEnd());
    for (KLDAP::LdapAttrValue::ConstIterator it = lst.constBegin(); it != end; ++it) {
        if (already) {
            res += sep;
        }

        already = true;
        res += asUtf8(*it);
    }

    return res;
}

static QMap<QString, QString> &adrbookattr2ldap()
{
    static QMap<QString, QString> keys;

    if (keys.isEmpty()) {
        keys[i18nc("@item LDAP search key", "Title")] = QStringLiteral("title");
        keys[i18n("Full Name")] = QStringLiteral("cn");
        keys[i18nc("@item LDAP search key", "Email")] = QStringLiteral("mail");
        keys[i18n("Home Number")] = QStringLiteral("homePhone");
        keys[i18n("Work Number")] = QStringLiteral("telephoneNumber");
        keys[i18n("Mobile Number")] = QStringLiteral("mobile");
        keys[i18n("Fax Number")] = QStringLiteral("facsimileTelephoneNumber");
        keys[i18n("Pager")] = QStringLiteral("pager");
        keys[i18n("Street")] = QStringLiteral("street");
        keys[i18nc("@item LDAP search key", "State")] = QStringLiteral("st");
        keys[i18n("Country")] = QStringLiteral("co");
        keys[i18n("City")] = QStringLiteral("l"); // krazy:exclude=doublequote_chars
        keys[i18n("Organization")] = QStringLiteral("o"); // krazy:exclude=doublequote_chars
        keys[i18n("Company")] = QStringLiteral("Company");
        keys[i18n("Department")] = QStringLiteral("department");
        keys[i18n("Zip Code")] = QStringLiteral("postalCode");
        keys[i18n("Postal Address")] = QStringLiteral("postalAddress");
        keys[i18n("Description")] = QStringLiteral("description");
        keys[i18n("User ID")] = QStringLiteral("uid");
    }

    return keys;
}

static QString makeFilter(const QString &query, LdapSearchDialog::FilterType attr, bool startsWith)
{
    /* The reasoning behind this filter is:
     * If it's a person, or a distlist, show it, even if it doesn't have an email address.
     * If it's not a person, or a distlist, only show it if it has an email attribute.
     * This allows both resource accounts with an email address which are not a person and
     * person entries without an email address to show up, while still not showing things
     * like structural entries in the ldap tree. */
    QString result(QStringLiteral("&(|(objectclass=person)(objectclass=groupofnames)(mail=*))("));
    if (query.isEmpty()) {
        // Return a filter that matches everything
        return result + QStringLiteral("|(cn=*)(sn=*)") + QLatin1Char(')');
    }

    if (attr == LdapSearchDialog::Name) {
        result += startsWith ? QStringLiteral("|(cn=%1*)(sn=%2*)") : QStringLiteral("|(cn=*%1*)(sn=*%2*)");
        result = result.arg(query, query);
    } else {
        result += startsWith ? QStringLiteral("%1=%2*") : QStringLiteral("%1=*%2*");
        if (attr == LdapSearchDialog::Email) {
            result = result.arg(QStringLiteral("mail"), query);
        } else if (attr == LdapSearchDialog::HomeNumber) {
            result = result.arg(QStringLiteral("homePhone"), query);
        } else if (attr == LdapSearchDialog::WorkNumber) {
            result = result.arg(QStringLiteral("telephoneNumber"), query);
        } else {
            // Error?
            result.clear();
            return result;
        }
    }
    result += QLatin1Char(')');
    return result;
}

static KContacts::Addressee convertLdapAttributesToAddressee(const KLDAP::LdapAttrMap &attrs)
{
    KContacts::Addressee addr;

    // name
    if (!attrs.value(QStringLiteral("cn")).isEmpty()) {
        addr.setNameFromString(asUtf8(attrs[QStringLiteral("cn")].first()));
    }

    // email
    KLDAP::LdapAttrValue lst = attrs[QStringLiteral("mail")];
    KLDAP::LdapAttrValue::ConstIterator it = lst.constBegin();
    bool pref = true;
    while (it != lst.constEnd()) {
        KContacts::Email email(asUtf8(*it));
        email.setPreferred(pref);
        addr.addEmail(email);
        pref = false;
        ++it;
    }

    if (!attrs.value(QStringLiteral("o")).isEmpty()) {
        addr.setOrganization(asUtf8(attrs[QStringLiteral("o")].first()));
    }
    if (addr.organization().isEmpty() && !attrs.value(QStringLiteral("Company")).isEmpty()) {
        addr.setOrganization(asUtf8(attrs[QStringLiteral("Company")].first()));
    }

    // Address
    KContacts::Address workAddr(KContacts::Address::Work);

    if (!attrs.value(QStringLiteral("department")).isEmpty()) {
        addr.setDepartment(asUtf8(attrs[QStringLiteral("department")].first()));
    }

    if (!workAddr.isEmpty()) {
        addr.insertAddress(workAddr);
    }

    // phone
    if (!attrs.value(QStringLiteral("homePhone")).isEmpty()) {
        KContacts::PhoneNumber homeNr = asUtf8(attrs[QStringLiteral("homePhone")].first());
        homeNr.setType(KContacts::PhoneNumber::Home);
        addr.insertPhoneNumber(homeNr);
    }

    if (!attrs.value(QStringLiteral("telephoneNumber")).isEmpty()) {
        KContacts::PhoneNumber workNr = asUtf8(attrs[QStringLiteral("telephoneNumber")].first());
        workNr.setType(KContacts::PhoneNumber::Work);
        addr.insertPhoneNumber(workNr);
    }

    if (!attrs.value(QStringLiteral("facsimileTelephoneNumber")).isEmpty()) {
        KContacts::PhoneNumber faxNr = asUtf8(attrs[QStringLiteral("facsimileTelephoneNumber")].first());
        faxNr.setType(KContacts::PhoneNumber::Fax);
        addr.insertPhoneNumber(faxNr);
    }

    if (!attrs.value(QStringLiteral("mobile")).isEmpty()) {
        KContacts::PhoneNumber cellNr = asUtf8(attrs[QStringLiteral("mobile")].first());
        cellNr.setType(KContacts::PhoneNumber::Cell);
        addr.insertPhoneNumber(cellNr);
    }

    if (!attrs.value(QStringLiteral("pager")).isEmpty()) {
        KContacts::PhoneNumber pagerNr = asUtf8(attrs[QStringLiteral("pager")].first());
        pagerNr.setType(KContacts::PhoneNumber::Pager);
        addr.insertPhoneNumber(pagerNr);
    }

    return addr;
}

class ContactListModel : public QAbstractTableModel
{
public:
    enum Role { ServerRole = Qt::UserRole + 1 };

    explicit ContactListModel(QObject *parent)
        : QAbstractTableModel(parent)
    {
    }

    void addContact(const KLDAP::LdapAttrMap &contact, const QString &server)
    {
        beginResetModel();
        mContactList.append(contact);
        mServerList.append(server);
        endResetModel();
    }

    Q_REQUIRED_RESULT QPair<KLDAP::LdapAttrMap, QString> contact(const QModelIndex &index) const
    {
        if (!index.isValid() || index.row() < 0 || index.row() >= mContactList.count()) {
            return qMakePair(KLDAP::LdapAttrMap(), QString());
        }

        return qMakePair(mContactList.at(index.row()), mServerList.at(index.row()));
    }

    Q_REQUIRED_RESULT QString email(const QModelIndex &index) const
    {
        if (!index.isValid() || index.row() < 0 || index.row() >= mContactList.count()) {
            return {};
        }

        return asUtf8(mContactList.at(index.row()).value(QStringLiteral("mail")).first()).trimmed();
    }

    Q_REQUIRED_RESULT QString fullName(const QModelIndex &index) const
    {
        if (!index.isValid() || index.row() < 0 || index.row() >= mContactList.count()) {
            return {};
        }

        return asUtf8(mContactList.at(index.row()).value(QStringLiteral("cn")).first()).trimmed();
    }

    void clear()
    {
        beginResetModel();
        mContactList.clear();
        mServerList.clear();
        endResetModel();
    }

    Q_REQUIRED_RESULT int rowCount(const QModelIndex &parent = QModelIndex()) const override
    {
        if (!parent.isValid()) {
            return mContactList.count();
        } else {
            return 0;
        }
    }

    Q_REQUIRED_RESULT int columnCount(const QModelIndex &parent = QModelIndex()) const override
    {
        if (!parent.isValid()) {
            return 18;
        } else {
            return 0;
        }
    }

    Q_REQUIRED_RESULT QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override
    {
        if (orientation == Qt::Vertical || role != Qt::DisplayRole || section < 0 || section > 17) {
            return {};
        }

        switch (section) {
        case 0:
            return i18n("Full Name");
        case 1:
            return i18nc("@title:column Column containing email addresses", "Email");
        case 2:
            return i18n("Home Number");
        case 3:
            return i18n("Work Number");
        case 4:
            return i18n("Mobile Number");
        case 5:
            return i18n("Fax Number");
        case 6:
            return i18n("Company");
        case 7:
            return i18n("Organization");
        case 8:
            return i18n("Street");
        case 9:
            return i18nc("@title:column Column containing the residential state of the address", "State");
        case 10:
            return i18n("Country");
        case 11:
            return i18n("Zip Code");
        case 12:
            return i18n("Postal Address");
        case 13:
            return i18n("City");
        case 14:
            return i18n("Department");
        case 15:
            return i18n("Description");
        case 16:
            return i18n("User ID");
        case 17:
            return i18nc("@title:column Column containing title of the person", "Title");
        default:
            return {};
        }
    }

    Q_REQUIRED_RESULT QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override
    {
        if (!index.isValid()) {
            return {};
        }

        if (index.row() < 0 || index.row() >= mContactList.count() || index.column() < 0 || index.column() > 17) {
            return {};
        }

        if (role == ServerRole) {
            return mServerList.at(index.row());
        }

        if ((role != Qt::DisplayRole) && (role != Qt::ToolTipRole)) {
            return {};
        }

        const KLDAP::LdapAttrMap map = mContactList.at(index.row());

        switch (index.column()) {
        case 0:
            return join(map.value(QStringLiteral("cn")), QStringLiteral(", "));
        case 1:
            return join(map.value(QStringLiteral("mail")), QStringLiteral(", "));
        case 2:
            return join(map.value(QStringLiteral("homePhone")), QStringLiteral(", "));
        case 3:
            return join(map.value(QStringLiteral("telephoneNumber")), QStringLiteral(", "));
        case 4:
            return join(map.value(QStringLiteral("mobile")), QStringLiteral(", "));
        case 5:
            return join(map.value(QStringLiteral("facsimileTelephoneNumber")), QStringLiteral(", "));
        case 6:
            return join(map.value(QStringLiteral("Company")), QStringLiteral(", "));
        case 7:
            return join(map.value(QStringLiteral("o")), QStringLiteral(", "));
        case 8:
            return join(map.value(QStringLiteral("street")), QStringLiteral(", "));
        case 9:
            return join(map.value(QStringLiteral("st")), QStringLiteral(", "));
        case 10:
            return join(map.value(QStringLiteral("co")), QStringLiteral(", "));
        case 11:
            return join(map.value(QStringLiteral("postalCode")), QStringLiteral(", "));
        case 12:
            return join(map.value(QStringLiteral("postalAddress")), QStringLiteral(", "));
        case 13:
            return join(map.value(QStringLiteral("l")), QStringLiteral(", "));
        case 14:
            return join(map.value(QStringLiteral("department")), QStringLiteral(", "));
        case 15:
            return join(map.value(QStringLiteral("description")), QStringLiteral(", "));
        case 16:
            return join(map.value(QStringLiteral("uid")), QStringLiteral(", "));
        case 17:
            return join(map.value(QStringLiteral("title")), QStringLiteral(", "));
        default:
            return {};
        }
    }

private:
    QVector<KLDAP::LdapAttrMap> mContactList;
    QStringList mServerList;
};

class Q_DECL_HIDDEN LdapSearchDialog::LdapSearchDialogPrivate
{
public:
    LdapSearchDialogPrivate(LdapSearchDialog *qq)
        : q(qq)
    {
    }

    QVector<QPair<KLDAP::LdapAttrMap, QString>> selectedItems()
    {
        QVector<QPair<KLDAP::LdapAttrMap, QString>> contacts;

        const QModelIndexList selected = mResultView->selectionModel()->selectedRows();
        const int numberOfSelectedElement(selected.count());
        contacts.reserve(numberOfSelectedElement);
        for (int i = 0; i < numberOfSelectedElement; ++i) {
            contacts.append(mModel->contact(sortproxy->mapToSource(selected.at(i))));
        }

        return contacts;
    }

    void saveSettings();
    void restoreSettings();
    void cancelQuery();

    void slotAddResult(const KLDAP::LdapClient &, const KLDAP::LdapObject &);
    void slotSetScope(bool);
    void slotStartSearch();
    void slotStopSearch();
    void slotSearchDone();
    void slotError(const QString &);
    void slotSelectAll();
    void slotUnselectAll();
    void slotSelectionChanged();

    LdapSearchDialog *const q;
    KGuiItem startSearchGuiItem;
    KGuiItem stopSearchGuiItem;
    int mNumHosts = 0;
    QList<KLDAP::LdapClient *> mLdapClientList;
    bool mIsConfigured = false;
    KContacts::Addressee::List mSelectedContacts;

    QComboBox *mFilterCombo = nullptr;
    QComboBox *mSearchType = nullptr;
    QLineEdit *mSearchEdit = nullptr;

    QCheckBox *mRecursiveCheckbox = nullptr;
    QTableView *mResultView = nullptr;
    QPushButton *mSearchButton = nullptr;
    ContactListModel *mModel = nullptr;
    KPIM::ProgressIndicatorLabel *progressIndication = nullptr;
    QSortFilterProxyModel *sortproxy = nullptr;
    QLineEdit *searchLine = nullptr;
    QPushButton *user1Button = nullptr;
};

LdapSearchDialog::LdapSearchDialog(QWidget *parent)
    : QDialog(parent)
    , d(new LdapSearchDialogPrivate(this))
{
    setWindowTitle(i18nc("@title:window", "Import Contacts from LDAP"));
    auto mainLayout = new QVBoxLayout(this);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Cancel, this);
    d->user1Button = new QPushButton;
    buttonBox->addButton(d->user1Button, QDialogButtonBox::ActionRole);

    auto user2Button = new QPushButton;
    buttonBox->addButton(user2Button, QDialogButtonBox::ActionRole);

    connect(d->user1Button, &QPushButton::clicked, this, &LdapSearchDialog::slotUser1);
    connect(user2Button, &QPushButton::clicked, this, &LdapSearchDialog::slotUser2);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &LdapSearchDialog::slotCancelClicked);
    d->user1Button->setDefault(true);
    setModal(false);
    KGuiItem::assign(buttonBox->button(QDialogButtonBox::Cancel), KStandardGuiItem::close());
    auto page = new QFrame(this);
    mainLayout->addWidget(page);
    mainLayout->addWidget(buttonBox);

    auto topLayout = new QVBoxLayout(page);
    topLayout->setContentsMargins({});

    auto groupBox = new QGroupBox(i18n("Search for Addresses in Directory"), page);
    auto boxLayout = new QGridLayout();
    groupBox->setLayout(boxLayout);
    boxLayout->setColumnStretch(1, 1);

    auto label = new QLabel(i18n("Search for:"), groupBox);
    boxLayout->addWidget(label, 0, 0);

    d->mSearchEdit = new QLineEdit(groupBox);
    d->mSearchEdit->setClearButtonEnabled(true);
    boxLayout->addWidget(d->mSearchEdit, 0, 1);
    label->setBuddy(d->mSearchEdit);

    label = new QLabel(i18nc("In LDAP attribute", "in"), groupBox);
    boxLayout->addWidget(label, 0, 2);

    d->mFilterCombo = new QComboBox(groupBox);
    d->mFilterCombo->addItem(i18nc("@item:inlistbox Name of the contact", "Name"), QVariant::fromValue(Name));
    d->mFilterCombo->addItem(i18nc("@item:inlistbox email address of the contact", "Email"), QVariant::fromValue(Email));
    d->mFilterCombo->addItem(i18nc("@item:inlistbox", "Home Number"), QVariant::fromValue(HomeNumber));
    d->mFilterCombo->addItem(i18nc("@item:inlistbox", "Work Number"), QVariant::fromValue(WorkNumber));
    boxLayout->addWidget(d->mFilterCombo, 0, 3);
    d->startSearchGuiItem = KGuiItem(i18nc("@action:button Start searching", "&Search"), QStringLiteral("edit-find"));
    d->stopSearchGuiItem = KStandardGuiItem::stop();

    QSize buttonSize;
    d->mSearchButton = new QPushButton(groupBox);
    KGuiItem::assign(d->mSearchButton, d->startSearchGuiItem);

    buttonSize = d->mSearchButton->sizeHint();
    if (buttonSize.width() < d->mSearchButton->sizeHint().width()) {
        buttonSize = d->mSearchButton->sizeHint();
    }
    d->mSearchButton->setFixedWidth(buttonSize.width());

    d->mSearchButton->setDefault(true);
    boxLayout->addWidget(d->mSearchButton, 0, 4);

    d->mRecursiveCheckbox = new QCheckBox(i18n("Recursive search"), groupBox);
    d->mRecursiveCheckbox->setChecked(true);
    boxLayout->addWidget(d->mRecursiveCheckbox, 1, 0, 1, 5);

    d->mSearchType = new QComboBox(groupBox);
    d->mSearchType->addItem(i18n("Contains"));
    d->mSearchType->addItem(i18n("Starts With"));
    boxLayout->addWidget(d->mSearchType, 1, 3, 1, 2);

    topLayout->addWidget(groupBox);

    auto quickSearchLineLayout = new QHBoxLayout;
    quickSearchLineLayout->addStretch();
    d->searchLine = new QLineEdit;
    new KPIM::LineEditCatchReturnKey(d->searchLine, this);
    d->searchLine->setClearButtonEnabled(true);
    d->searchLine->setPlaceholderText(i18n("Search in result"));
    quickSearchLineLayout->addWidget(d->searchLine);
    topLayout->addLayout(quickSearchLineLayout);

    d->mResultView = new QTableView(page);
    d->mResultView->setSelectionMode(QTableView::MultiSelection);
    d->mResultView->setSelectionBehavior(QTableView::SelectRows);
    d->mModel = new ContactListModel(d->mResultView);

    d->sortproxy = new QSortFilterProxyModel(this);
    d->sortproxy->setFilterKeyColumn(-1); // Search in all column
    d->sortproxy->setSourceModel(d->mModel);
    d->sortproxy->setFilterCaseSensitivity(Qt::CaseInsensitive);
    connect(d->searchLine, &QLineEdit::textChanged, d->sortproxy, &QSortFilterProxyModel::setFilterFixedString);

    d->mResultView->setModel(d->sortproxy);
    d->mResultView->verticalHeader()->hide();
    d->mResultView->setSortingEnabled(true);
    d->mResultView->horizontalHeader()->setSortIndicatorShown(true);
    connect(d->mResultView, &QTableView::clicked, this, [this]() {
        d->slotSelectionChanged();
    });
    topLayout->addWidget(d->mResultView);

    d->mResultView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(d->mResultView, &QTableView::customContextMenuRequested, this, &LdapSearchDialog::slotCustomContextMenuRequested);

    auto buttonLayout = new QHBoxLayout;
    buttonLayout->setContentsMargins({});
    topLayout->addLayout(buttonLayout);

    d->progressIndication = new KPIM::ProgressIndicatorLabel(i18n("Searching..."));
    buttonLayout->addWidget(d->progressIndication);

    auto buttons = new QDialogButtonBox(page);
    QPushButton *button = buttons->addButton(i18n("Select All"), QDialogButtonBox::ActionRole);
    connect(button, &QPushButton::clicked, this, [this]() {
        d->slotSelectAll();
    });
    button = buttons->addButton(i18n("Unselect All"), QDialogButtonBox::ActionRole);
    connect(button, &QPushButton::clicked, this, [this]() {
        d->slotUnselectAll();
    });

    buttonLayout->addWidget(buttons);

    d->user1Button->setText(i18n("Add Selected"));
    user2Button->setText(i18n("Configure LDAP Servers..."));

    connect(d->mRecursiveCheckbox, &QCheckBox::toggled, this, [this](bool state) {
        d->slotSetScope(state);
    });
    connect(d->mSearchButton, SIGNAL(clicked()), this, SLOT(slotStartSearch()));

    setTabOrder(d->mSearchEdit, d->mFilterCombo);
    setTabOrder(d->mFilterCombo, d->mSearchButton);
    d->mSearchEdit->setFocus();

    d->slotSelectionChanged();
    d->restoreSettings();
}

LdapSearchDialog::~LdapSearchDialog()
{
    d->saveSettings();
}

void LdapSearchDialog::setSearchText(const QString &text)
{
    d->mSearchEdit->setText(text);
}

KContacts::Addressee::List LdapSearchDialog::selectedContacts() const
{
    return d->mSelectedContacts;
}

void LdapSearchDialog::slotCustomContextMenuRequested(const QPoint &pos)
{
    const QModelIndex index = d->mResultView->indexAt(pos);
    if (index.isValid()) {
        QMenu menu(this);
        QAction *act = menu.addAction(i18n("Copy"));
        if (menu.exec(QCursor::pos()) == act) {
            QClipboard *cb = QApplication::clipboard();
            cb->setText(index.data().toString(), QClipboard::Clipboard);
        }
    }
}

void LdapSearchDialog::LdapSearchDialogPrivate::slotSelectionChanged()
{
    user1Button->setEnabled(mResultView->selectionModel()->hasSelection());
}

void LdapSearchDialog::LdapSearchDialogPrivate::restoreSettings()
{
    // Create one KLDAP::LdapClient per selected server and configure it.

    // First clean the list to make sure it is empty at
    // the beginning of the process
    qDeleteAll(mLdapClientList);
    mLdapClientList.clear();

    KConfig *config = KLDAP::LdapClientSearchConfig::config();

    KConfigGroup searchGroup(config, "LDAPSearch");
    mSearchType->setCurrentIndex(searchGroup.readEntry("SearchType", 0));

    // then read the config file and register all selected
    // server in the list
    KConfigGroup group(config, "LDAP");
    mNumHosts = group.readEntry("NumSelectedHosts", 0);
    if (!mNumHosts) {
        mIsConfigured = false;
    } else {
        mIsConfigured = true;
        auto clientSearchConfig = new KLDAP::LdapClientSearchConfig;
        for (int j = 0; j < mNumHosts; ++j) {
            auto ldapClient = new KLDAP::LdapClient(0, q);
            auto job = new KLDAP::LdapSearchClientReadConfigServerJob(q);
            job->setCurrentIndex(j);
            job->setActive(true);
            job->setConfig(group);
            job->setLdapClient(ldapClient);
            job->start();
            QStringList attrs;

            QMap<QString, QString>::ConstIterator end(adrbookattr2ldap().constEnd());
            for (QMap<QString, QString>::ConstIterator it = adrbookattr2ldap().constBegin(); it != end; ++it) {
                attrs << *it;
            }

            ldapClient->setAttributes(attrs);

            // clang-format off
            q->connect(ldapClient, SIGNAL(result(KLDAP::LdapClient,KLDAP::LdapObject)), q, SLOT(slotAddResult(KLDAP::LdapClient,KLDAP::LdapObject)));
            // clang-format on
            q->connect(ldapClient, SIGNAL(done()), q, SLOT(slotSearchDone()));
            q->connect(ldapClient, &KLDAP::LdapClient::error, q, [this](const QString &err) {
                slotError(err);
            });

            mLdapClientList.append(ldapClient);
        }
        delete clientSearchConfig;

        mModel->clear();
    }
    KConfigGroup groupHeader(config, "Headers");
    mResultView->horizontalHeader()->restoreState(groupHeader.readEntry("HeaderState", QByteArray()));

    KConfigGroup groupSize(config, "Size");
    const QSize dialogSize = groupSize.readEntry("Size", QSize());
    if (dialogSize.isValid()) {
        q->resize(dialogSize);
    } else {
        q->resize(QSize(600, 400).expandedTo(q->minimumSizeHint()));
    }
}

void LdapSearchDialog::LdapSearchDialogPrivate::saveSettings()
{
    KConfig *config = KLDAP::LdapClientSearchConfig::config();
    KConfigGroup group(config, "LDAPSearch");
    group.writeEntry("SearchType", mSearchType->currentIndex());

    KConfigGroup groupHeader(config, "Headers");
    groupHeader.writeEntry("HeaderState", mResultView->horizontalHeader()->saveState());
    groupHeader.sync();

    KConfigGroup size(config, "Size");
    size.writeEntry("Size", q->size());
    size.sync();

    group.sync();
}

void LdapSearchDialog::LdapSearchDialogPrivate::cancelQuery()
{
    for (KLDAP::LdapClient *client : std::as_const(mLdapClientList)) {
        client->cancelQuery();
    }
}

void LdapSearchDialog::LdapSearchDialogPrivate::slotAddResult(const KLDAP::LdapClient &client, const KLDAP::LdapObject &obj)
{
    mModel->addContact(obj.attributes(), client.server().host());
}

void LdapSearchDialog::LdapSearchDialogPrivate::slotSetScope(bool rec)
{
    for (KLDAP::LdapClient *client : std::as_const(mLdapClientList)) {
        if (rec) {
            client->setScope(QStringLiteral("sub"));
        } else {
            client->setScope(QStringLiteral("one"));
        }
    }
}

void LdapSearchDialog::LdapSearchDialogPrivate::slotStartSearch()
{
    cancelQuery();

    if (!mIsConfigured) {
        KMessageBox::error(q, i18n("You must select an LDAP server before searching."));
        q->slotUser2();
        return;
    }

#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
    KGuiItem::assign(mSearchButton, stopSearchGuiItem);
    progressIndication->start();

    q->disconnect(mSearchButton, SIGNAL(clicked()), q, SLOT(slotStartSearch()));
    q->connect(mSearchButton, SIGNAL(clicked()), q, SLOT(slotStopSearch()));

    const bool startsWith = (mSearchType->currentIndex() == 1);

    const QString filter = makeFilter(mSearchEdit->text().trimmed(), mFilterCombo->currentData().value<FilterType>(), startsWith);

    // loop in the list and run the KLDAP::LdapClients
    mModel->clear();
    for (KLDAP::LdapClient *client : std::as_const(mLdapClientList)) {
        client->startQuery(filter);
    }

    saveSettings();
}

void LdapSearchDialog::LdapSearchDialogPrivate::slotStopSearch()
{
    cancelQuery();
    slotSearchDone();
}

void LdapSearchDialog::LdapSearchDialogPrivate::slotSearchDone()
{
    // If there are no more active clients, we are done.
    for (KLDAP::LdapClient *client : std::as_const(mLdapClientList)) {
        if (client->isActive()) {
            return;
        }
    }

    q->disconnect(mSearchButton, SIGNAL(clicked()), q, SLOT(slotStopSearch()));
    q->connect(mSearchButton, SIGNAL(clicked()), q, SLOT(slotStartSearch()));

    KGuiItem::assign(mSearchButton, startSearchGuiItem);
    progressIndication->stop();
#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif
}

void LdapSearchDialog::LdapSearchDialogPrivate::slotError(const QString &error)
{
#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif
    KMessageBox::error(q, error);
}

void LdapSearchDialog::closeEvent(QCloseEvent *e)
{
    d->slotStopSearch();
    e->accept();
}

void LdapSearchDialog::LdapSearchDialogPrivate::slotUnselectAll()
{
    mResultView->clearSelection();
    slotSelectionChanged();
}

void LdapSearchDialog::LdapSearchDialogPrivate::slotSelectAll()
{
    mResultView->selectAll();
    slotSelectionChanged();
}

void LdapSearchDialog::slotUser1()
{
    // Import selected items

    d->mSelectedContacts.clear();

    const QVector<QPair<KLDAP::LdapAttrMap, QString>> &items = d->selectedItems();

    if (!items.isEmpty()) {
        const QDateTime now = QDateTime::currentDateTime();

        for (int i = 0; i < items.count(); ++i) {
            KContacts::Addressee contact = convertLdapAttributesToAddressee(items.at(i).first);

            // set a comment where the contact came from
            contact.setNote(i18nc("arguments are host name, datetime",
                                  "Imported from LDAP directory %1 on %2",
                                  items.at(i).second,
                                  QLocale().toString(now, QLocale::ShortFormat)));

            d->mSelectedContacts.append(contact);
        }
    }

    d->slotStopSearch();
    Q_EMIT contactsAdded();

    accept();
}

void LdapSearchDialog::slotUser2()
{
    // Configure LDAP servers

    QPointer<KCMultiDialog> dialog = new KCMultiDialog(this);
    dialog->setWindowTitle(i18nc("@title:window", "Configure the Address Book LDAP Settings"));
    dialog->addModule(KPluginMetaData(QStringLiteral("pim" QT_STRINGIFY(QT_VERSION_MAJOR)) + QStringLiteral("/kcms/kaddressbook/kcm_ldap")));

    if (dialog->exec()) { // krazy:exclude=crashy
        d->restoreSettings();
    }
    delete dialog;
}

void LdapSearchDialog::slotCancelClicked()
{
    d->slotStopSearch();
    reject();
}

#include "moc_ldapsearchdialog.cpp"
