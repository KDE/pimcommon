/*
   SPDX-FileCopyrightText: 2017-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "addresseelineeditakonadisearch.h"
#include "baloocompletionemail.h"
#include <KConfigGroup>
#include <KSharedConfig>

using namespace PimCommon;

AddresseeLineEditAkonadiSearch::AddresseeLineEditAkonadiSearch()
    : mBalooCompletionEmail(new PimCommon::BalooCompletionEmail)
{
    loadBalooBlackList();
}

AddresseeLineEditAkonadiSearch::~AddresseeLineEditAkonadiSearch()
{
    delete mBalooCompletionEmail;
}

int AddresseeLineEditAkonadiSearch::balooCompletionSource() const
{
    return mBalooCompletionSource;
}

void AddresseeLineEditAkonadiSearch::setBalooCompletionSource(int value)
{
    mBalooCompletionSource = value;
}

QStringList AddresseeLineEditAkonadiSearch::balooBlackList() const
{
    return mBalooCompletionEmail->balooCompletionEmailInfo().mBlackList;
}

QStringList AddresseeLineEditAkonadiSearch::domainExcludeList() const
{
    return mBalooCompletionEmail->balooCompletionEmailInfo().mExcludeDomains;
}

void AddresseeLineEditAkonadiSearch::loadBalooBlackList()
{
    KSharedConfig::Ptr config = KSharedConfig::openConfig(QStringLiteral("kpimbalooblacklist"));
    config->reparseConfiguration();
    KConfigGroup group(config, QStringLiteral("AddressLineEdit"));
    PimCommon::BalooCompletionEmail::BalooCompletionEmailInfo info;
    const QStringList balooBlackList = group.readEntry("BalooBackList", QStringList());
    const QStringList domainExcludeList = group.readEntry("ExcludeDomain", QStringList());
    const QStringList lstExcludeEmailsRegularExpressions = group.readEntry("ExcludeEmailsRegexp", QStringList());

    info.mExcludeEmailsRegularExpressions = lstExcludeEmailsRegularExpressions;
    info.mBlackList = balooBlackList;
    info.mExcludeDomains = domainExcludeList;
    mBalooCompletionEmail->setBalooCompletionEmailInfo(info);
}

QStringList AddresseeLineEditAkonadiSearch::cleanupEmailList(const QStringList &inputList)
{
    PimCommon::BalooCompletionEmail::BalooCompletionEmailInfo info = mBalooCompletionEmail->balooCompletionEmailInfo();
    info.mListEmail = inputList;
    mBalooCompletionEmail->setBalooCompletionEmailInfo(info);
    return mBalooCompletionEmail->cleanupEmailList();
}
