/*
  SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "completionconfiguredialog.h"
#include <KConfigGroup>
#include <KLDAPWidgets/LdapClientSearch>
#include <KLocalizedString>
#include <KSharedConfig>
#include <KWindowConfig>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QWindow>

#include <addressline/completionorder/completionorderwidget.h>
#include <config-akonadi-search.h>
#if !DISABLE_AKONADI_SEARCH
#include <addressline/blacklistbaloocompletion/blacklistbalooemailcompletionwidget.h>
#endif
#include <addressline/recentaddress/recentaddresswidget.h>

using namespace PimCommon;
namespace
{
static const char myCompletionConfigureDialogGroupName[] = "CompletionConfigureDialog";
}
class PimCommon::CompletionConfigureDialogPrivate
{
public:
    CompletionConfigureDialogPrivate() = default;

    QTabWidget *mTabWidget = nullptr;
    PimCommon::CompletionOrderWidget *mCompletionOrderWidget = nullptr;
#if !DISABLE_AKONADI_SEARCH
    PimCommon::BlackListBalooEmailCompletionWidget *mBlackListBalooWidget = nullptr;
#endif
    PimCommon::RecentAddressWidget *mRecentaddressWidget = nullptr;
};

CompletionConfigureDialog::CompletionConfigureDialog(QWidget *parent)
    : QDialog(parent)
    , d(new PimCommon::CompletionConfigureDialogPrivate)
{
    setWindowTitle(i18nc("@title:window", "Configure Completion"));
    auto mainLayout = new QVBoxLayout(this);

    d->mTabWidget = new QTabWidget(this);
    d->mTabWidget->setObjectName(QStringLiteral("tabwidget"));
    mainLayout->addWidget(d->mTabWidget);

    d->mCompletionOrderWidget = new PimCommon::CompletionOrderWidget(this);
    d->mCompletionOrderWidget->setObjectName(QStringLiteral("completionorder_widget"));
    d->mTabWidget->addTab(d->mCompletionOrderWidget, i18n("Completion Order"));

    d->mRecentaddressWidget = new PimCommon::RecentAddressWidget(this);
    d->mRecentaddressWidget->setObjectName(QStringLiteral("recentaddress_widget"));
    d->mTabWidget->addTab(d->mRecentaddressWidget, i18n("Recent Address"));

#if !DISABLE_AKONADI_SEARCH
    d->mBlackListBalooWidget = new PimCommon::BlackListBalooEmailCompletionWidget(this);
    d->mBlackListBalooWidget->setObjectName(QStringLiteral("blacklistbaloo_widget"));
    d->mTabWidget->addTab(d->mBlackListBalooWidget, i18n("Blacklist Email Address"));
#endif

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Apply | QDialogButtonBox::Cancel, this);
    buttonBox->setObjectName(QStringLiteral("buttonbox"));
    connect(buttonBox, &QDialogButtonBox::accepted, this, &CompletionConfigureDialog::slotSaveAndClose);
    connect(buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked, this, &CompletionConfigureDialog::slotSave);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    mainLayout->addWidget(buttonBox);
    readConfig();
}

CompletionConfigureDialog::~CompletionConfigureDialog()
{
    writeConfig();
}

void CompletionConfigureDialog::readConfig()
{
    create(); // ensure a window is created
    windowHandle()->resize(QSize(600, 400));
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1String(myCompletionConfigureDialogGroupName));
    KWindowConfig::restoreWindowSize(windowHandle(), group);
    resize(windowHandle()->size()); // workaround for QTBUG-40584
}

void CompletionConfigureDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1String(myCompletionConfigureDialogGroupName));
    KWindowConfig::saveWindowSize(windowHandle(), group);
}

void CompletionConfigureDialog::setRecentAddresses(const QStringList &lst)
{
    d->mRecentaddressWidget->setAddresses(lst);
}

void CompletionConfigureDialog::setLdapClientSearch(KLDAPWidgets::LdapClientSearch *ldapSearch)
{
    d->mCompletionOrderWidget->setLdapClientSearch(ldapSearch);
}

void CompletionConfigureDialog::load()
{
    d->mCompletionOrderWidget->loadCompletionItems();
#if !DISABLE_AKONADI_SEARCH
    d->mBlackListBalooWidget->load();
#endif
}

bool CompletionConfigureDialog::recentAddressWasChanged() const
{
    return d->mRecentaddressWidget->wasChanged();
}

void CompletionConfigureDialog::storeAddresses(KConfig *config)
{
    d->mRecentaddressWidget->storeAddresses(config);
}

void CompletionConfigureDialog::slotSaveAndClose()
{
    slotSave();
    accept();
}

void CompletionConfigureDialog::slotSave()
{
#if !DISABLE_AKONADI_SEARCH
    d->mBlackListBalooWidget->save();
#endif
    d->mCompletionOrderWidget->save();
}

void CompletionConfigureDialog::setEmailBlackList(const QStringList &lst)
{
#if !DISABLE_AKONADI_SEARCH
    d->mBlackListBalooWidget->setEmailBlackList(lst);
#endif
}

#include "moc_completionconfiguredialog.cpp"
