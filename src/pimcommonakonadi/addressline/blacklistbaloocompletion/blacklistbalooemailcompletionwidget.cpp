/*
  SPDX-FileCopyrightText: 2015-2024 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "blacklistbalooemailcompletionwidget.h"
using namespace Qt::Literals::StringLiterals;

#include "blacklistbalooemaillist.h"
#include "blacklistbalooemailsearchjob.h"
#include "blacklistbalooemailutil.h"
#include "blacklistbalooemailwarning.h"
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
#include <QVBoxLayout>

using namespace PimCommon;
BlackListBalooEmailCompletionWidget::BlackListBalooEmailCompletionWidget(QWidget *parent)
    : QWidget(parent)
    , mNumberOfEmailsFound(new QLabel(this))
    , mSearchLineEdit(new QLineEdit(this))
    , mExcludeDomainLineEdit(new QLineEdit(this))
    , mEmailList(new BlackListBalooEmailList(this))
    , mSearchButton(new QPushButton(QIcon::fromTheme(QStringLiteral("edit-find")), i18n("Search"), this))
    , mSelectButton(new QPushButton(i18n("&Select"), this))
    , mUnselectButton(new QPushButton(i18n("&Unselect"), this))
    , mShowAllBlackListedEmails(new QPushButton(i18n("Show Blacklisted Emails"), this))
    , mMoreResult(new QLabel(i18n("<qt><a href=\"more_result\">More result...</a></qt>"), this))
    , mBlackListWarning(new BlackListBalooEmailWarning(this))
    , mExcludeEmailFromRegularExpressionLineEdit(new QLineEdit(this))
{
    auto mainLayout = new QVBoxLayout(this);

    auto searchLayout = new QHBoxLayout;
    mainLayout->addLayout(searchLayout);

    auto lab = new QLabel(i18n("Search email:"), this);
    lab->setObjectName("search_label"_L1);
    searchLayout->addWidget(lab);

    mSearchLineEdit->setPlaceholderText(i18n("Research is done from 3 characters"));
    mSearchLineEdit->setFocus();
    mSearchLineEdit->setClearButtonEnabled(true);
    KLineEditEventHandler::catchReturnKey(mSearchLineEdit);
    mSearchLineEdit->setObjectName("search_lineedit"_L1);
    connect(mSearchLineEdit, &QLineEdit::returnPressed, this, &BlackListBalooEmailCompletionWidget::slotCheckIfUpdateBlackListIsNeeded);
    searchLayout->addWidget(mSearchLineEdit);

    mSearchButton->setObjectName("search_button"_L1);
    connect(mSearchButton, &QAbstractButton::clicked, this, &BlackListBalooEmailCompletionWidget::slotCheckIfUpdateBlackListIsNeeded);
    mSearchButton->setEnabled(false);
    searchLayout->addWidget(mSearchButton);

    mShowAllBlackListedEmails->setObjectName("show_blacklisted_email_button"_L1);
    connect(mShowAllBlackListedEmails, &QAbstractButton::clicked, this, &BlackListBalooEmailCompletionWidget::slotShowAllBlacklistedEmail);
    searchLayout->addWidget(mShowAllBlackListedEmails);

    mEmailList->setObjectName("email_list"_L1);
    mainLayout->addWidget(mEmailList);

    mBlackListWarning->setObjectName("backlistwarning"_L1);
    connect(mBlackListWarning, &BlackListBalooEmailWarning::newSearch, this, &BlackListBalooEmailCompletionWidget::slotSearch);
    connect(mBlackListWarning, &BlackListBalooEmailWarning::saveChanges, this, &BlackListBalooEmailCompletionWidget::slotSaveChanges);
    mainLayout->addWidget(mBlackListWarning);

    auto searchLineLayout = new QHBoxLayout;
    mainLayout->addLayout(searchLineLayout);

    auto selectElementLayout = new QHBoxLayout;
    searchLineLayout->addLayout(selectElementLayout);

    mSelectButton->setObjectName("select_email"_L1);
    connect(mSelectButton, &QAbstractButton::clicked, this, &BlackListBalooEmailCompletionWidget::slotSelectEmails);
    selectElementLayout->addWidget(mSelectButton);

    mUnselectButton->setObjectName("unselect_email"_L1);
    connect(mUnselectButton, &QAbstractButton::clicked, this, &BlackListBalooEmailCompletionWidget::slotUnselectEmails);
    selectElementLayout->addWidget(mUnselectButton);

    mMoreResult->setObjectName("moreresultlabel"_L1);
    selectElementLayout->addWidget(mMoreResult);

    mMoreResult->setContextMenuPolicy(Qt::NoContextMenu);
    connect(mMoreResult, &QLabel::linkActivated, this, &BlackListBalooEmailCompletionWidget::slotLinkClicked);
    mMoreResult->setVisible(false);
    selectElementLayout->addStretch(1);

    connect(mSearchLineEdit, &QLineEdit::textChanged, this, &BlackListBalooEmailCompletionWidget::slotSearchLineEditChanged);

    mSearchInResultLineEdit = new KListWidgetSearchLine(this, mEmailList);
    mSearchInResultLineEdit->setObjectName("searchinresultlineedit"_L1);
    mSearchInResultLineEdit->setClearButtonEnabled(true);
    mSearchInResultLineEdit->setPlaceholderText(i18n("Search in result..."));
    KLineEditEventHandler::catchReturnKey(mSearchInResultLineEdit);

    searchLineLayout->addStretch(0);
    mNumberOfEmailsFound->setObjectName("numberofemailsfound"_L1);

    searchLineLayout->addWidget(mNumberOfEmailsFound, 1);
    searchLineLayout->addWidget(mSearchInResultLineEdit);

    auto excludeDomainLayout = new QHBoxLayout;
    excludeDomainLayout->setContentsMargins({});
    mainLayout->addLayout(excludeDomainLayout);

    auto excludeDomainLabel = new QLabel(i18n("Exclude domain names:"), this);
    excludeDomainLabel->setObjectName("domain_label"_L1);
    excludeDomainLayout->addWidget(excludeDomainLabel);

    excludeDomainLayout->addWidget(mExcludeDomainLineEdit);
    mExcludeDomainLineEdit->setObjectName("domain_lineedit"_L1);
    mExcludeDomainLineEdit->setClearButtonEnabled(true);
    KLineEditEventHandler::catchReturnKey(mExcludeDomainLineEdit);
    mExcludeDomainLineEdit->setPlaceholderText(i18n("Separate domain with \'%1\'", QLatin1Char(',')));

    auto excludeEmailRegularExpressionLayout = new QHBoxLayout;
    excludeEmailRegularExpressionLayout->setContentsMargins({});
    mainLayout->addLayout(excludeEmailRegularExpressionLayout);

    auto excludeEmailRegularExpressionLabel = new QLabel(i18n("Exclude email with Regular Expression:"), this);
    excludeEmailRegularExpressionLabel->setObjectName("email_regularexpression_label"_L1);
    excludeEmailRegularExpressionLayout->addWidget(excludeEmailRegularExpressionLabel);

    excludeEmailRegularExpressionLayout->addWidget(mExcludeEmailFromRegularExpressionLineEdit);
    mExcludeEmailFromRegularExpressionLineEdit->setObjectName("exclude_email_lineedit"_L1);
    mExcludeEmailFromRegularExpressionLineEdit->setClearButtonEnabled(true);
    KLineEditEventHandler::catchReturnKey(mExcludeEmailFromRegularExpressionLineEdit);
    mExcludeEmailFromRegularExpressionLineEdit->setPlaceholderText(i18n("Separate regular expression with \'%1\'", QLatin1Char(',')));

    connect(mEmailList, &QListWidget::itemSelectionChanged, this, &BlackListBalooEmailCompletionWidget::slotSelectionChanged);
    slotSelectionChanged();
    connect(mEmailList, &QListWidget::customContextMenuRequested, this, &BlackListBalooEmailCompletionWidget::slotCustomContextMenuRequested);
}

BlackListBalooEmailCompletionWidget::~BlackListBalooEmailCompletionWidget() = default;

void BlackListBalooEmailCompletionWidget::slotSelectionChanged()
{
    const bool selectionIsNotEmpty = !mEmailList->selectedItems().isEmpty();
    mSelectButton->setEnabled(selectionIsNotEmpty);
    mUnselectButton->setEnabled(selectionIsNotEmpty);
}

void BlackListBalooEmailCompletionWidget::slotCustomContextMenuRequested(const QPoint &pos)
{
    const bool selectionIsNotEmpty = !mEmailList->selectedItems().isEmpty();
    if (selectionIsNotEmpty) {
        QMenu menu(this);
        menu.addAction(i18n("Select"), this, &BlackListBalooEmailCompletionWidget::slotSelectEmails);
        menu.addSeparator();
        menu.addAction(i18n("Unselect"), this, &BlackListBalooEmailCompletionWidget::slotUnselectEmails);
        menu.exec(mapToGlobal(pos));
    }
}

void BlackListBalooEmailCompletionWidget::load()
{
    KSharedConfig::Ptr config = KSharedConfig::openConfig(QStringLiteral("kpimbalooblacklist"));
    KConfigGroup group(config, QStringLiteral("AddressLineEdit"));

    const QStringList lstExcludeEmailsRegularExpressions = group.readEntry("ExcludeEmailsRegexp", QStringList());
    mEmailList->setExcludeEmailsRegularExpressions(lstExcludeEmailsRegularExpressions);
    mExcludeEmailFromRegularExpressionLineEdit->setText(lstExcludeEmailsRegularExpressions.join(QLatin1Char(',')));
    mOriginalExcludeEmailRegexp = lstExcludeEmailsRegularExpressions;

    const QStringList lstExcludeDomains = group.readEntry("ExcludeDomain", QStringList());
    mEmailList->setExcludeDomains(lstExcludeDomains);
    mExcludeDomainLineEdit->setText(lstExcludeDomains.join(QLatin1Char(',')));
    mOriginalExcludeDomain = lstExcludeDomains;
    slotSelectionChanged();
}

void BlackListBalooEmailCompletionWidget::save()
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
        PimCommon::BlackListBalooEmailUtil util;
        util.initialBlackList(blackList);
        util.setNewBlackList(result);
        blackList = util.createNewBlackList();
        group.writeEntry("BalooBackList", blackList);
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

void BlackListBalooEmailCompletionWidget::slotSaveChanges()
{
    // TODO avoid to save a lot.
    const QHash<QString, bool> result = mEmailList->blackListItemChanged();
    KSharedConfig::Ptr config = KSharedConfig::openConfig(QStringLiteral("kpimbalooblacklist"));
    KConfigGroup group(config, QStringLiteral("AddressLineEdit"));
    QStringList blackList = group.readEntry("BalooBackList", QStringList());
    PimCommon::BlackListBalooEmailUtil util;
    util.initialBlackList(blackList);
    util.setNewBlackList(result);
    blackList = util.createNewBlackList();
    group.writeEntry("BalooBackList", blackList);
    group.sync();
    mEmailList->setEmailBlackList(blackList);
    slotSearch();
}

void BlackListBalooEmailCompletionWidget::slotUnselectEmails()
{
    const QList<QListWidgetItem *> lstSelected = mEmailList->selectedItems();
    for (QListWidgetItem *item : lstSelected) {
        item->setCheckState(Qt::Unchecked);
    }
}

void BlackListBalooEmailCompletionWidget::slotSelectEmails()
{
    const QList<QListWidgetItem *> lstSelected = mEmailList->selectedItems();
    for (QListWidgetItem *item : lstSelected) {
        item->setCheckState(Qt::Checked);
    }
}

void BlackListBalooEmailCompletionWidget::slotSearchLineEditChanged(const QString &text)
{
    mSearchButton->setEnabled(text.trimmed().length() > 2);
    hideMoreResultAndChangeLimit();
}

void BlackListBalooEmailCompletionWidget::hideMoreResultAndChangeLimit()
{
    mMoreResult->setVisible(false);
    mLimit = 500;
}

void BlackListBalooEmailCompletionWidget::slotSearch()
{
    const QString searchEmail = mSearchLineEdit->text().trimmed();
    if (searchEmail.length() > 2) {
        mSearchInResultLineEdit->clear();
        auto job = new PimCommon::BlackListBalooEmailSearchJob(this);
        job->setSearchEmail(searchEmail);
        job->setLimit(mLimit);
        connect(job, &BlackListBalooEmailSearchJob::emailsFound, this, &BlackListBalooEmailCompletionWidget::slotEmailFound);
        if (!job->start()) {
            qCWarning(PIMCOMMONAKONADI_LOG) << "Impossible to start search job";
        }
    }
}

void BlackListBalooEmailCompletionWidget::slotEmailFound(const QStringList &list)
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

void BlackListBalooEmailCompletionWidget::setEmailBlackList(const QStringList &list)
{
    mEmailList->setEmailBlackList(list);
}

void BlackListBalooEmailCompletionWidget::slotCheckIfUpdateBlackListIsNeeded()
{
    const QHash<QString, bool> result = mEmailList->blackListItemChanged();
    if (result.isEmpty()) {
        slotSearch();
    } else {
        mBlackListWarning->animatedShow();
    }
}

void BlackListBalooEmailCompletionWidget::slotLinkClicked(const QString &link)
{
    if (link == "more_result"_L1) {
        mLimit += 200;
        slotSearch();
    }
}

void BlackListBalooEmailCompletionWidget::slotShowAllBlacklistedEmail()
{
    KSharedConfig::Ptr config = KSharedConfig::openConfig(QStringLiteral("kpimbalooblacklist"));
    KConfigGroup group(config, QStringLiteral("AddressLineEdit"));
    const QStringList balooBlackList = group.readEntry("BalooBackList", QStringList());
    slotEmailFound(balooBlackList);
}

#include "moc_blacklistbalooemailcompletionwidget.cpp"
