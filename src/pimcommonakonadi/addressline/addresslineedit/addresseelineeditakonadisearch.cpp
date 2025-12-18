/*
   SPDX-FileCopyrightText: 2017-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "addresseelineeditakonadisearch.h"
#include "../addresseelineutil.h"
#include "akonadisearchcompletionemail.h"
#include <KConfigGroup>
#include <KSharedConfig>

using namespace Qt::Literals;
using namespace PimCommon;

AddresseeLineEditAkonadiSearch::AddresseeLineEditAkonadiSearch()
    : mAkonadiSearchCompletionEmail(new PimCommon::AkonadiSearchCompletionEmail)
{
    loadAkonadiSearchBlackList();
}

AddresseeLineEditAkonadiSearch::~AddresseeLineEditAkonadiSearch()
{
    delete mAkonadiSearchCompletionEmail;
}

int AddresseeLineEditAkonadiSearch::akonadiSearchCompletionSource() const
{
    return mAkonadiSearchCompletionSource;
}

void AddresseeLineEditAkonadiSearch::setAkonadiSearchCompletionSource(int value)
{
    mAkonadiSearchCompletionSource = value;
}

QStringList AddresseeLineEditAkonadiSearch::akonadiSearchBlackList() const
{
    return mAkonadiSearchCompletionEmail->balooCompletionEmailInfo().mBlackList;
}

QStringList AddresseeLineEditAkonadiSearch::domainExcludeList() const
{
    return mAkonadiSearchCompletionEmail->balooCompletionEmailInfo().mExcludeDomains;
}

void AddresseeLineEditAkonadiSearch::loadAkonadiSearchBlackList()
{
    KSharedConfig::Ptr config = KSharedConfig::openConfig(QStringLiteral("kpimbalooblacklist"));
    config->reparseConfiguration();
    KConfigGroup group(config, QStringLiteral("AddressLineEdit"));
    PimCommon::AkonadiSearchCompletionEmail::AkonadiSearchCompletionEmailInfo info;
    const QStringList balooBlackList = group.readEntry("BalooBackList", QStringList());
    const QStringList domainExcludeList = group.readEntry("ExcludeDomain", QStringList());
    const QStringList lstExcludeEmailsRegularExpressions =
        group.readEntry("ExcludeEmailsRegexp", PimCommon::AddresseeLineUtil::excludeEmailsRegularExpression());

    info.mExcludeEmailsRegularExpressions = lstExcludeEmailsRegularExpressions;
    info.mBlackList = balooBlackList;
    info.mExcludeDomains = domainExcludeList;
    mAkonadiSearchCompletionEmail->setBalooCompletionEmailInfo(info);
}

QStringList AddresseeLineEditAkonadiSearch::cleanupEmailList(const QStringList &inputList)
{
    PimCommon::AkonadiSearchCompletionEmail::AkonadiSearchCompletionEmailInfo info = mAkonadiSearchCompletionEmail->balooCompletionEmailInfo();
    info.mListEmail = inputList;
    mAkonadiSearchCompletionEmail->setBalooCompletionEmailInfo(info);
    return mAkonadiSearchCompletionEmail->cleanupEmailList();
}
