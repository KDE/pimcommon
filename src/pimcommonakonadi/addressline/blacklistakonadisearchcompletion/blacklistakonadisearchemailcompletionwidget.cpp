/*
  SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "blacklistakonadisearchemailcompletionwidget.h"

#include "../addresseelineutil.h"
#include "blacklistakonadisearchemaillist.h"
#include "blacklistakonadisearchemailsearchjob.h"
#include "blacklistakonadisearchemailutil.h"
#include "blacklistakonadisearchemailwarning.h"
#include <KLineEditEventHandler>

#include "pimcommonakonadi_debug.h"
#include <KConfigGroup>
#include <KListWidgetSearchLine>
#include <KLocalizedString>
#include <KSharedConfig>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMenu>
#include <QPushButton>
#include <QTimer>
#include <QVBoxLayout>
#include <chrono>
using namespace std::chrono_literals;

using namespace PimCommon;
using namespace Qt::Literals::StringLiterals;
BlackListAkonadiSearchEmailCompletionWidget::BlackListAkonadiSearchEmailCompletionWidget(QWidget *parent)
    : QWidget(parent)
    , mNumberOfEmailsFound(new QLabel(this))
    , mSearchLineEdit(new QLineEdit(this))
    , mExcludeDomainLineEdit(new QLineEdit(this))
    , mEmailList(new BlackListAkonadiSearchEmailList(this))
    , mShowAllBlackListedEmails(new QPushButton(i18nc("@action:button", "Show Blacklisted Emails"), this))
    , mMoreResult(new QLabel(i18nc("@label:textbox", "<qt><a href=\"more_result\">More result...</a></qt>"), this))
    , mBlackListWarning(new BlackListAkonadiSearchEmailWarning(this))
    , mExcludeEmailFromRegularExpressionLineEdit(new QLineEdit(this))
{
    auto mainLayout = new QVBoxLayout(this);

    auto searchLayout = new QHBoxLayout;
    mainLayout->addLayout(searchLayout);

    mSearchLineEdit->setPlaceholderText(i18nc("@info:placeholder", "Research is done from 3 characters"));
    mSearchLineEdit->setFocus();
    mSearchLineEdit->setClearButtonEnabled(true);
    KLineEditEventHandler::catchReturnKey(mSearchLineEdit);
    mSearchLineEdit->addAction(QIcon::fromTheme(u"edit-find"_s), QLineEdit::LeadingPosition);
    mSearchLineEdit->setObjectName("search_lineedit"_L1);
    connect(mSearchLineEdit, &QLineEdit::returnPressed, this, &BlackListAkonadiSearchEmailCompletionWidget::slotCheckIfUpdateBlackListIsNeeded);
    searchLayout->addWidget(mSearchLineEdit);

    mShowAllBlackListedEmails->setObjectName("show_blacklisted_email_button"_L1);
    connect(mShowAllBlackListedEmails, &QAbstractButton::clicked, this, &BlackListAkonadiSearchEmailCompletionWidget::slotShowAllBlacklistedEmail);
    searchLayout->addWidget(mShowAllBlackListedEmails);

    mEmailList->setObjectName("email_list"_L1);
    mainLayout->addWidget(mEmailList);

    mBlackListWarning->setObjectName("backlistwarning"_L1);
    connect(mBlackListWarning, &BlackListAkonadiSearchEmailWarning::newSearch, this, &BlackListAkonadiSearchEmailCompletionWidget::slotSearch);
    connect(mBlackListWarning, &BlackListAkonadiSearchEmailWarning::saveChanges, this, &BlackListAkonadiSearchEmailCompletionWidget::slotSaveChanges);
    mainLayout->addWidget(mBlackListWarning);

    auto searchLineLayout = new QHBoxLayout;
    mainLayout->addLayout(searchLineLayout);

    auto selectElementLayout = new QHBoxLayout;
    searchLineLayout->addLayout(selectElementLayout);

    mMoreResult->setObjectName("moreresultlabel"_L1);
    selectElementLayout->addWidget(mMoreResult);

    mMoreResult->setContextMenuPolicy(Qt::NoContextMenu);
    connect(mMoreResult, &QLabel::linkActivated, this, &BlackListAkonadiSearchEmailCompletionWidget::slotLinkClicked);
    mMoreResult->setVisible(false);
    selectElementLayout->addStretch(1);

    connect(mSearchLineEdit, &QLineEdit::textChanged, this, &BlackListAkonadiSearchEmailCompletionWidget::slotSearchLineEditChanged);
    searchLineLayout->addStretch(0);
    mNumberOfEmailsFound->setObjectName("numberofemailsfound"_L1);

    searchLineLayout->addWidget(mNumberOfEmailsFound, 1);

    auto excludeDomainLayout = new QHBoxLayout;
    excludeDomainLayout->setContentsMargins({});
    mainLayout->addLayout(excludeDomainLayout);

    auto excludeDomainLabel = new QLabel(i18nc("@label:textbox", "Exclude domain names:"), this);
    excludeDomainLabel->setObjectName("domain_label"_L1);
    excludeDomainLayout->addWidget(excludeDomainLabel);

    excludeDomainLayout->addWidget(mExcludeDomainLineEdit);
    mExcludeDomainLineEdit->setObjectName("domain_lineedit"_L1);
    mExcludeDomainLineEdit->setClearButtonEnabled(true);
    KLineEditEventHandler::catchReturnKey(mExcludeDomainLineEdit);
    mExcludeDomainLineEdit->setPlaceholderText(i18nc("@info:placeholder", "Separate domain with \'%1\'", QLatin1Char(',')));

    auto excludeEmailRegularExpressionLayout = new QHBoxLayout;
    excludeEmailRegularExpressionLayout->setContentsMargins({});
    mainLayout->addLayout(excludeEmailRegularExpressionLayout);

    auto excludeEmailRegularExpressionLabel = new QLabel(i18nc("@label:textbox", "Exclude email with Regular Expression:"), this);
    excludeEmailRegularExpressionLabel->setObjectName("email_regularexpression_label"_L1);
    excludeEmailRegularExpressionLayout->addWidget(excludeEmailRegularExpressionLabel);

    excludeEmailRegularExpressionLayout->addWidget(mExcludeEmailFromRegularExpressionLineEdit);
    mExcludeEmailFromRegularExpressionLineEdit->setObjectName("exclude_email_lineedit"_L1);
    mExcludeEmailFromRegularExpressionLineEdit->setClearButtonEnabled(true);
    KLineEditEventHandler::catchReturnKey(mExcludeEmailFromRegularExpressionLineEdit);
    mExcludeEmailFromRegularExpressionLineEdit->setPlaceholderText(i18nc("@info:placeholder", "Separate regular expression with \'%1\'", QLatin1Char(',')));

    connect(mEmailList, &QListWidget::customContextMenuRequested, this, &BlackListAkonadiSearchEmailCompletionWidget::slotCustomContextMenuRequested);
}

BlackListAkonadiSearchEmailCompletionWidget::~BlackListAkonadiSearchEmailCompletionWidget() = default;

void BlackListAkonadiSearchEmailCompletionWidget::slotCustomContextMenuRequested(const QPoint &pos)
{
    const bool selectionIsNotEmpty = !mEmailList->selectedItems().isEmpty();
    if (selectionIsNotEmpty) {
        QMenu menu(this);
        menu.addAction(i18n("Select"), this, &BlackListAkonadiSearchEmailCompletionWidget::slotSelectEmails);
        menu.addSeparator();
        menu.addAction(i18n("Unselect"), this, &BlackListAkonadiSearchEmailCompletionWidget::slotUnselectEmails);
        menu.exec(mapToGlobal(pos));
    }
}

void BlackListAkonadiSearchEmailCompletionWidget::load()
{
    KSharedConfig::Ptr config = KSharedConfig::openConfig(QStringLiteral("kpimbalooblacklist"));
    KConfigGroup group(config, QStringLiteral("AddressLineEdit"));

    const QStringList lstExcludeEmailsRegularExpressions =
        group.readEntry("ExcludeEmailsRegexp", PimCommon::AddresseeLineUtil::excludeEmailsRegularExpression());
    mEmailList->setExcludeEmailsRegularExpressions(lstExcludeEmailsRegularExpressions);
    mExcludeEmailFromRegularExpressionLineEdit->setText(lstExcludeEmailsRegularExpressions.join(QLatin1Char(',')));
    mOriginalExcludeEmailRegexp = lstExcludeEmailsRegularExpressions;

    const QStringList lstExcludeDomains = group.readEntry("ExcludeDomain", QStringList());
    mEmailList->setExcludeDomains(lstExcludeDomains);
    mExcludeDomainLineEdit->setText(lstExcludeDomains.join(QLatin1Char(',')));
    mOriginalExcludeDomain = lstExcludeDomains;
}

void BlackListAkonadiSearchEmailCompletionWidget::restoreToDefaults()
{
    mExcludeDomainLineEdit->clear();
    mExcludeEmailFromRegularExpressionLineEdit->setText(PimCommon::AddresseeLineUtil::excludeEmailsRegularExpression().join(QLatin1Char(',')));
}

void BlackListAkonadiSearchEmailCompletionWidget::save()
{
    const QString excludeEmailsRegexp = mExcludeEmailFromRegularExpressionLineEdit->text().remove(QLatin1Char(' '));
    const QStringList newExcludeEmailsRegExp = excludeEmailsRegexp.split(QLatin1Char(','), Qt::SkipEmptyParts);
    bool needToSave = (mOriginalExcludeEmailRegexp != newExcludeEmailsRegExp);

    const QString excludeDomains = mExcludeDomainLineEdit->text().remove(QLatin1Char(' '));
    const QStringList newExcludeDomain = excludeDomains.split(QLatin1Char(','), Qt::SkipEmptyParts);
    needToSave |= (mOriginalExcludeDomain != newExcludeDomain);

    KSharedConfig::Ptr config = KSharedConfig::openConfig(QStringLiteral("kpimbalooblacklist"));
    KConfigGroup group(config, QStringLiteral("AddressLineEdit"));
    const QHash<QString, bool> result = mEmailList->blackListItemChanged();
    if (!result.isEmpty()) {
        needToSave = true;
        QStringList blackList = group.readEntry("BalooBackList", QStringList());
        PimCommon::BlackListAkonadiSearchEmailUtil util;
        util.initialBlackList(blackList);
        util.setNewBlackList(result);
        blackList = util.createNewBlackList();
        group.writeEntry("BalooBackList", blackList);
        mEmailList->setEmailBlackList(blackList);
    }
    if (needToSave) {
        group.writeEntry("ExcludeEmailsRegexp", newExcludeEmailsRegExp);
        mEmailList->setExcludeEmailsRegularExpressions(newExcludeEmailsRegExp);
        mOriginalExcludeEmailRegexp = newExcludeEmailsRegExp;

        group.writeEntry("ExcludeDomain", newExcludeDomain);
        mEmailList->setExcludeDomains(newExcludeDomain);
        mOriginalExcludeDomain = newExcludeDomain;
        group.sync();
    }
    config->reparseConfiguration();
}

void BlackListAkonadiSearchEmailCompletionWidget::slotSaveChanges()
{
    // TODO avoid to save a lot.
    const QHash<QString, bool> result = mEmailList->blackListItemChanged();
    KSharedConfig::Ptr config = KSharedConfig::openConfig(QStringLiteral("kpimbalooblacklist"));
    KConfigGroup group(config, QStringLiteral("AddressLineEdit"));
    QStringList blackList = group.readEntry("BalooBackList", QStringList());
    PimCommon::BlackListAkonadiSearchEmailUtil util;
    util.initialBlackList(blackList);
    util.setNewBlackList(result);
    blackList = util.createNewBlackList();
    group.writeEntry("BalooBackList", blackList);
    group.sync();
    mEmailList->setEmailBlackList(blackList);
    slotSearch();
}

void BlackListAkonadiSearchEmailCompletionWidget::slotUnselectEmails()
{
    const QList<QListWidgetItem *> lstSelected = mEmailList->selectedItems();
    for (QListWidgetItem *item : lstSelected) {
        item->setCheckState(Qt::Unchecked);
    }
}

void BlackListAkonadiSearchEmailCompletionWidget::slotSelectEmails()
{
    const QList<QListWidgetItem *> lstSelected = mEmailList->selectedItems();
    for (QListWidgetItem *item : lstSelected) {
        item->setCheckState(Qt::Checked);
    }
}

void BlackListAkonadiSearchEmailCompletionWidget::slotSearchLineEditChanged(const QString &text)
{
    const bool enabled = text.trimmed().length() > 2;
    hideMoreResultAndChangeLimit();
    if (enabled) {
        if (!mSearchTimer) {
            mSearchTimer = new QTimer(this);
            connect(mSearchTimer, &QTimer::timeout, this, &BlackListAkonadiSearchEmailCompletionWidget::slotSearchTimerFired);
        } else {
            mSearchTimer->stop(); // eventually
        }

        mSearchTimer->setSingleShot(true);
        mSearchTimer->start(1s);
    }
}

void BlackListAkonadiSearchEmailCompletionWidget::slotSearchTimerFired()
{
    // A search is pending.
    if (mSearchTimer) {
        mSearchTimer->stop();
    }
    slotCheckIfUpdateBlackListIsNeeded();
}

void BlackListAkonadiSearchEmailCompletionWidget::hideMoreResultAndChangeLimit()
{
    mMoreResult->setVisible(false);
    mLimit = 500;
}

void BlackListAkonadiSearchEmailCompletionWidget::slotSearch()
{
    const QString searchEmail = mSearchLineEdit->text().trimmed();
    if (searchEmail.length() > 2) {
        auto job = new PimCommon::BlackListAkonadiSearchEmailSearchJob(this);
        job->setSearchEmail(searchEmail);
        job->setLimit(mLimit);
        connect(job, &BlackListAkonadiSearchEmailSearchJob::emailsFound, this, &BlackListAkonadiSearchEmailCompletionWidget::slotEmailFound);
        if (!job->start()) {
            qCWarning(PIMCOMMONAKONADI_LOG) << "Impossible to start search job";
        }
    }
}

void BlackListAkonadiSearchEmailCompletionWidget::slotEmailFound(const QStringList &list)
{
    const int numberOfEmails = mEmailList->setEmailFound(list);
    mMoreResult->setVisible(numberOfEmails == mLimit);
    mEmailList->scrollToBottom();
    if (numberOfEmails == 0) {
        mNumberOfEmailsFound->setText(i18n("No email found."));
    } else {
        mNumberOfEmailsFound->setText(i18np("1 email found", "%1 emails found", numberOfEmails));
    }
}

void BlackListAkonadiSearchEmailCompletionWidget::setEmailBlackList(const QStringList &list)
{
    mEmailList->setEmailBlackList(list);
}

void BlackListAkonadiSearchEmailCompletionWidget::slotCheckIfUpdateBlackListIsNeeded()
{
    const QHash<QString, bool> result = mEmailList->blackListItemChanged();
    if (result.isEmpty()) {
        slotSearch();
    } else {
        mBlackListWarning->animatedShow();
    }
}

void BlackListAkonadiSearchEmailCompletionWidget::slotLinkClicked(const QString &link)
{
    if (link == "more_result"_L1) {
        mLimit += 200;
        slotSearch();
    }
}

void BlackListAkonadiSearchEmailCompletionWidget::slotShowAllBlacklistedEmail()
{
    KSharedConfig::Ptr config = KSharedConfig::openConfig(QStringLiteral("kpimbalooblacklist"));
    KConfigGroup group(config, QStringLiteral("AddressLineEdit"));
    const QStringList balooBlackList = group.readEntry("BalooBackList", QStringList());
    slotEmailFound(balooBlackList);
}

#include "moc_blacklistakonadisearchemailcompletionwidget.cpp"
