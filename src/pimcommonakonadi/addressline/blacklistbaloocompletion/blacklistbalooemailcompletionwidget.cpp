/*
  SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "blacklistbalooemailcompletionwidget.h"
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
    lab->setObjectName(QStringLiteral("search_label"));
    searchLayout->addWidget(lab);

    mSearchLineEdit->setPlaceholderText(i18n("Research is done from 3 characters"));
    mSearchLineEdit->setFocus();
    mSearchLineEdit->setClearButtonEnabled(true);
    KLineEditEventHandler::catchReturnKey(mSearchLineEdit);
    mSearchLineEdit->setObjectName(QStringLiteral("search_lineedit"));
    connect(mSearchLineEdit, &QLineEdit::returnPressed, this, &BlackListBalooEmailCompletionWidget::slotCheckIfUpdateBlackListIsNeeded);
    searchLayout->addWidget(mSearchLineEdit);

    mSearchButton->setObjectName(QStringLiteral("search_button"));
    connect(mSearchButton, &QAbstractButton::clicked, this, &BlackListBalooEmailCompletionWidget::slotCheckIfUpdateBlackListIsNeeded);
    mSearchButton->setEnabled(false);
    searchLayout->addWidget(mSearchButton);

    mShowAllBlackListedEmails->setObjectName(QStringLiteral("show_blacklisted_email_button"));
    connect(mShowAllBlackListedEmails, &QAbstractButton::clicked, this, &BlackListBalooEmailCompletionWidget::slotShowAllBlacklistedEmail);
    searchLayout->addWidget(mShowAllBlackListedEmails);

    mEmailList->setObjectName(QStringLiteral("email_list"));
    mainLayout->addWidget(mEmailList);

    mBlackListWarning->setObjectName(QStringLiteral("backlistwarning"));
    connect(mBlackListWarning, &BlackListBalooEmailWarning::newSearch, this, &BlackListBalooEmailCompletionWidget::slotSearch);
    connect(mBlackListWarning, &BlackListBalooEmailWarning::saveChanges, this, &BlackListBalooEmailCompletionWidget::slotSaveChanges);
    mainLayout->addWidget(mBlackListWarning);

    auto searchLineLayout = new QHBoxLayout;
    mainLayout->addLayout(searchLineLayout);

    auto selectElementLayout = new QHBoxLayout;
    searchLineLayout->addLayout(selectElementLayout);

    mSelectButton->setObjectName(QStringLiteral("select_email"));
    connect(mSelectButton, &QAbstractButton::clicked, this, &BlackListBalooEmailCompletionWidget::slotSelectEmails);
    selectElementLayout->addWidget(mSelectButton);

    mUnselectButton->setObjectName(QStringLiteral("unselect_email"));
    connect(mUnselectButton, &QAbstractButton::clicked, this, &BlackListBalooEmailCompletionWidget::slotUnselectEmails);
    selectElementLayout->addWidget(mUnselectButton);

    mMoreResult->setObjectName(QStringLiteral("moreresultlabel"));
    selectElementLayout->addWidget(mMoreResult);

    mMoreResult->setContextMenuPolicy(Qt::NoContextMenu);
    connect(mMoreResult, &QLabel::linkActivated, this, &BlackListBalooEmailCompletionWidget::slotLinkClicked);
    mMoreResult->setVisible(false);
    selectElementLayout->addStretch(1);

    connect(mSearchLineEdit, &QLineEdit::textChanged, this, &BlackListBalooEmailCompletionWidget::slotSearchLineEditChanged);

    mSearchInResultLineEdit = new KListWidgetSearchLine(this, mEmailList);
    mSearchInResultLineEdit->setObjectName(QStringLiteral("searchinresultlineedit"));
    mSearchInResultLineEdit->setClearButtonEnabled(true);
    mSearchInResultLineEdit->setPlaceholderText(i18n("Search in result..."));
    KLineEditEventHandler::catchReturnKey(mSearchInResultLineEdit);

    searchLineLayout->addStretch(0);
    mNumberOfEmailsFound->setObjectName(QStringLiteral("numberofemailsfound"));

    searchLineLayout->addWidget(mNumberOfEmailsFound, 1);
    searchLineLayout->addWidget(mSearchInResultLineEdit);

    auto excludeDomainLayout = new QHBoxLayout;
    excludeDomainLayout->setContentsMargins({});
    mainLayout->addLayout(excludeDomainLayout);

    auto excludeDomainLabel = new QLabel(i18n("Exclude domain names:"), this);
    excludeDomainLabel->setObjectName(QStringLiteral("domain_label"));
    excludeDomainLayout->addWidget(excludeDomainLabel);

    excludeDomainLayout->addWidget(mExcludeDomainLineEdit);
    mExcludeDomainLineEdit->setObjectName(QStringLiteral("domain_lineedit"));
    mExcludeDomainLineEdit->setClearButtonEnabled(true);
    KLineEditEventHandler::catchReturnKey(mExcludeDomainLineEdit);
    mExcludeDomainLineEdit->setPlaceholderText(i18n("Separate domain with \'%1\'", QLatin1Char(',')));

    auto excludeEmailRegularExpressionLayout = new QHBoxLayout;
    excludeEmailRegularExpressionLayout->setContentsMargins({});
    mainLayout->addLayout(excludeEmailRegularExpressionLayout);

    auto excludeEmailRegularExpressionLabel = new QLabel(i18n("Exclude email with Regular Expression:"), this);
    excludeEmailRegularExpressionLabel->setObjectName(QStringLiteral("email_regularexpression_label"));
    excludeEmailRegularExpressionLayout->addWidget(excludeEmailRegularExpressionLabel);

    excludeEmailRegularExpressionLayout->addWidget(mExcludeEmailFromRegularExpressionLineEdit);
    mExcludeEmailFromRegularExpressionLineEdit->setObjectName(QStringLiteral("exclude_email_lineedit"));
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
    KConfigGroup group(config, "AddressLineEdit");

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
    KConfigGroup group(config, "AddressLineEdit");
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
    KConfigGroup group(config, "AddressLineEdit");
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
    if (link == QLatin1String("more_result")) {
        mLimit += 200;
        slotSearch();
    }
}

void BlackListBalooEmailCompletionWidget::slotShowAllBlacklistedEmail()
{
    KSharedConfig::Ptr config = KSharedConfig::openConfig(QStringLiteral("kpimbalooblacklist"));
    KConfigGroup group(config, "AddressLineEdit");
    const QStringList balooBlackList = group.readEntry("BalooBackList", QStringList());
    slotEmailFound(balooBlackList);
}

#include "moc_blacklistbalooemailcompletionwidget.cpp"
