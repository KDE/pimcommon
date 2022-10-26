/*
  SPDX-FileCopyrightText: 2015-2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "addresseelineeditmanager.h"
#include "addresseelineeditakonadi.h"
#include "addresseelineeditbaloo.h"
#include "addresseelineeditldap.h"
#include "kmailcompletion.h"

#include <KColorScheme>
#include <KConfigGroup>
#include <KLDAP/LdapClient>
#include <KSharedConfig>
#include <QCoreApplication>
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
#include "pimcommonakonadi_debug.h"
#include <QNetworkInformation>
#else
#include <QNetworkConfigurationManager>
#endif
#include <QTimer>

using namespace PimCommon;

Q_GLOBAL_STATIC(AddresseeLineEditManager, sInstance)

AddresseeLineEditManager::AddresseeLineEditManager()
    : mCompletion(new KMailCompletion)
    , mAddresseeLineEditAkonadi(new AddresseeLineEditAkonadi)
    , mAddressessLineEditLdap(new AddresseeLineEditLdap(this))
    , mAddressessLineEditBaloo(new AddresseeLineEditBaloo)
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    , mNetworkConfigMgr(new QNetworkConfigurationManager(QCoreApplication::instance()))
#endif
{
    KConfigGroup group(KSharedConfig::openConfig(), "AddressLineEdit");
    mShowOU = group.readEntry("ShowOU", false);
    mAutoGroupExpand = group.readEntry("AutoGroupExpand", false);
}

AddresseeLineEditManager::~AddresseeLineEditManager()
{
    delete mCompletion;

    delete mAddresseeLineEditAkonadi;
    delete mAddressessLineEditLdap;
    delete mAddressessLineEditBaloo;
}

AddresseeLineEditManager *AddresseeLineEditManager::self()
{
    return sInstance;
}

void AddresseeLineEditManager::updateCompletionOrder()
{
    updateLDAPWeights();
    updateCollectionWeights();
}

void AddresseeLineEditManager::updateCollectionWeights()
{
    akonadiCollectionToCompletionSourceMap.clear();
}

void AddresseeLineEditManager::updateLDAPWeights()
{
    mAddressessLineEditLdap->updateLDAPWeights();
}

int AddresseeLineEditManager::addCompletionSource(const QString &source, int weight)
{
    QMap<QString, int>::iterator it = completionSourceWeights.find(source);
    if (it == completionSourceWeights.end()) {
        completionSourceWeights.insert(source, weight);
    } else {
        completionSourceWeights[source] = weight;
    }

    const int sourceIndex = completionSources.indexOf(source);
    if (sourceIndex == -1) {
        completionSources.append(source);
        return completionSources.size() - 1;
    } else {
        return sourceIndex;
    }
}

void AddresseeLineEditManager::removeCompletionSource(const QString &source)
{
    QMap<QString, int>::iterator it = completionSourceWeights.find(source);
    if (it != completionSourceWeights.end()) {
        completionSourceWeights.remove(source);
        mCompletion->clear();
    }
}

Akonadi::Session *AddresseeLineEditManager::akonadiSession() const
{
    return mAddresseeLineEditAkonadi->akonadiSession();
}

KMailCompletion *AddresseeLineEditManager::completion() const
{
    return mCompletion;
}

AddresseeLineEdit *AddresseeLineEditManager::addressLineEdit() const
{
    return mAddressessLineEditLdap->addressLineEdit();
}

void AddresseeLineEditManager::setAddressLineEdit(AddresseeLineEdit *addressLineEdit)
{
    mAddressessLineEditLdap->setAddressLineEdit(addressLineEdit);
}

bool AddresseeLineEditManager::isOnline() const
{
#if QT_VERSION >= QT_VERSION_CHECK(6, 1, 0)
    if (QNetworkInformation::load(QNetworkInformation::Feature::Reachability)) {
        return QNetworkInformation::instance()->reachability() == QNetworkInformation::Reachability::Online;
    } else {
        qCWarning(PIMCOMMONAKONADI_LOG) << "Couldn't find a working backend for QNetworkInformation";
        return false;
    }
#else
    return mNetworkConfigMgr->isOnline();
#endif
}

KLDAP::LdapClientSearch *AddresseeLineEditManager::ldapSearch() const
{
    return mAddressessLineEditLdap->ldapSearch();
}

QTimer *AddresseeLineEditManager::ldapTimer() const
{
    return mAddressessLineEditLdap->ldapTimer();
}

int AddresseeLineEditManager::ldapClientToCompletionSourceValue(int value) const
{
    return mAddressessLineEditLdap->ldapClientToCompletionSourceValue(value);
}

bool AddresseeLineEditManager::isLdapClientToCompletionSourceMapContains(int value) const
{
    return mAddressessLineEditLdap->isLdapClientToCompletionSourceMapContains(value);
}

int AddresseeLineEditManager::balooCompletionSource() const
{
    return mAddressessLineEditBaloo->balooCompletionSource();
}

void AddresseeLineEditManager::setBalooCompletionSource(int value)
{
    mAddressessLineEditBaloo->setBalooCompletionSource(value);
}

void AddresseeLineEditManager::initializeLdap()
{
    mAddressessLineEditLdap->init();
}

QString AddresseeLineEditManager::ldapText() const
{
    return mAddressessLineEditLdap->ldapText();
}

void AddresseeLineEditManager::setLdapText(const QString &ldapText)
{
    mAddressessLineEditLdap->setLdapText(ldapText);
}

void AddresseeLineEditManager::stopLDAPLookup()
{
    mAddressessLineEditLdap->stopLDAPLookup();
}

void AddresseeLineEditManager::startLoadingLDAPEntries()
{
    mAddressessLineEditLdap->startLoadingLDAPEntries();
}

void AddresseeLineEditManager::restartLdap(const QString &searchString, AddresseeLineEdit *addressLine)
{
    mAddressessLineEditLdap->restartLdap(searchString, addressLine);
}

void AddresseeLineEditManager::loadBalooBlackList()
{
    mAddressessLineEditBaloo->loadBalooBlackList();
}

QStringList AddresseeLineEditManager::cleanupRecentAddressEmailList(const QStringList &inputList)
{
    if (inputList != mRecentAddressEmailList) {
        mRecentCleanupAddressEmailList = mAddressessLineEditBaloo->cleanupEmailList(inputList);
        mRecentAddressEmailList = inputList;
    }
    return mRecentCleanupAddressEmailList;
}

QStringList AddresseeLineEditManager::cleanupEmailList(const QStringList &inputList)
{
    return mAddressessLineEditBaloo->cleanupEmailList(inputList);
}

QStringList AddresseeLineEditManager::balooBlackList() const
{
    return mAddressessLineEditBaloo->balooBlackList();
}

bool AddresseeLineEditManager::showOU() const
{
    return mShowOU;
}

void AddresseeLineEditManager::setShowOU(bool checked)
{
    if (checked != mShowOU) {
        KConfigGroup group(KSharedConfig::openConfig(), "AddressLineEdit");
        group.writeEntry("ShowOU", checked);
        mShowOU = checked;
    }
}

bool AddresseeLineEditManager::autoGroupExpand() const
{
    return mAutoGroupExpand;
}

void AddresseeLineEditManager::setAutoGroupExpand(bool checked)
{
    if (mAutoGroupExpand != checked) {
        mAutoGroupExpand = checked;
        KConfigGroup group(KSharedConfig::openConfig(), "AddressLineEdit");
        group.writeEntry("AutoGroupExpand", mAutoGroupExpand);
    }
}

QColor AddresseeLineEditManager::alternateColor() const
{
    if (!mAlternateColor.isValid()) {
        const KColorScheme colorScheme(QPalette::Active, KColorScheme::View);
        mAlternateColor = colorScheme.background(KColorScheme::AlternateBackground).color();
    }
    return mAlternateColor;
}
