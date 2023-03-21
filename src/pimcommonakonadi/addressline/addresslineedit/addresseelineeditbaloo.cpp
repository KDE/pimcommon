/*
   SPDX-FileCopyrightText: 2017-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "addresseelineeditbaloo.h"
#include "baloocompletionemail.h"
#include <KConfigGroup>
#include <KSharedConfig>

using namespace PimCommon;

AddresseeLineEditBaloo::AddresseeLineEditBaloo()
    : mBalooCompletionEmail(new PimCommon::BalooCompletionEmail)
{
    loadBalooBlackList();
}

AddresseeLineEditBaloo::~AddresseeLineEditBaloo()
{
    delete mBalooCompletionEmail;
}

int AddresseeLineEditBaloo::balooCompletionSource() const
{
    return mBalooCompletionSource;
}

void AddresseeLineEditBaloo::setBalooCompletionSource(int value)
{
    mBalooCompletionSource = value;
}

QStringList AddresseeLineEditBaloo::balooBlackList() const
{
    return mBalooBlackList;
}

QStringList AddresseeLineEditBaloo::domainExcludeList() const
{
    return mDomainExcludeList;
}

void AddresseeLineEditBaloo::loadBalooBlackList()
{
    KSharedConfig::Ptr config = KSharedConfig::openConfig(QStringLiteral("kpimbalooblacklist"));
    config->reparseConfiguration();
    KConfigGroup group(config, "AddressLineEdit");
    PimCommon::BalooCompletionEmail::BalooCompletionEmailInfo info;
    mBalooBlackList = group.readEntry("BalooBackList", QStringList());
    mDomainExcludeList = group.readEntry("ExcludeDomain", QStringList());
    info.mBlackList = mBalooBlackList;
    info.mExcludeDomains = mDomainExcludeList;
    mBalooCompletionEmail->setBalooCompletionEmailInfo(info);
}

QStringList AddresseeLineEditBaloo::cleanupEmailList(const QStringList &inputList)
{
    PimCommon::BalooCompletionEmail::BalooCompletionEmailInfo info = mBalooCompletionEmail->balooCompletionEmailInfo();
    info.mListEmail = inputList;
    mBalooCompletionEmail->setBalooCompletionEmailInfo(info);
    return mBalooCompletionEmail->cleanupEmailList();
}
