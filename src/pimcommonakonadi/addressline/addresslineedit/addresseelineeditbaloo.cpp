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
    mBalooBlackList = group.readEntry("BalooBackList", QStringList());
    mDomainExcludeList = group.readEntry("ExcludeDomain", QStringList());
    mBalooCompletionEmail->setBlackList(mBalooBlackList);
    mBalooCompletionEmail->setExcludeDomain(mDomainExcludeList);
}

QStringList AddresseeLineEditBaloo::cleanupEmailList(const QStringList &inputList)
{
    mBalooCompletionEmail->setEmailList(inputList);
    return mBalooCompletionEmail->cleanupEmailList();
}
