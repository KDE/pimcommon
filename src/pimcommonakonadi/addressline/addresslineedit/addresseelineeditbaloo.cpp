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
    return mBalooCompletionEmail->balooCompletionEmailInfo().mBlackList;
}

QStringList AddresseeLineEditBaloo::domainExcludeList() const
{
    return mBalooCompletionEmail->balooCompletionEmailInfo().mExcludeDomains;
}

void AddresseeLineEditBaloo::loadBalooBlackList()
{
    KSharedConfig::Ptr config = KSharedConfig::openConfig(QStringLiteral("kpimbalooblacklist"));
    config->reparseConfiguration();
    KConfigGroup group(config, QLatin1String("AddressLineEdit"));
    PimCommon::BalooCompletionEmail::BalooCompletionEmailInfo info;
    const QStringList balooBlackList = group.readEntry("BalooBackList", QStringList());
    const QStringList domainExcludeList = group.readEntry("ExcludeDomain", QStringList());
    const QStringList lstExcludeEmailsRegularExpressions = group.readEntry("ExcludeEmailsRegexp", QStringList());

    info.mExcludeEmailsRegularExpressions = lstExcludeEmailsRegularExpressions;
    info.mBlackList = balooBlackList;
    info.mExcludeDomains = domainExcludeList;
    mBalooCompletionEmail->setBalooCompletionEmailInfo(info);
}

QStringList AddresseeLineEditBaloo::cleanupEmailList(const QStringList &inputList)
{
    PimCommon::BalooCompletionEmail::BalooCompletionEmailInfo info = mBalooCompletionEmail->balooCompletionEmailInfo();
    info.mListEmail = inputList;
    mBalooCompletionEmail->setBalooCompletionEmailInfo(info);
    return mBalooCompletionEmail->cleanupEmailList();
}
