/*
   Copyright (C) 2017-2020 Laurent Montel <montel@kde.org>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
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
