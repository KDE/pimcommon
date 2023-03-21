/*
   SPDX-FileCopyrightText: 2017-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once
#include "pimcommonakonadi_private_export.h"
#include <QStringList>

namespace PimCommon
{
class BalooCompletionEmail;
class PIMCOMMONAKONADI_TESTS_EXPORT AddresseeLineEditBaloo
{
public:
    AddresseeLineEditBaloo();
    ~AddresseeLineEditBaloo();

    Q_REQUIRED_RESULT int balooCompletionSource() const;
    void setBalooCompletionSource(int value);
    void loadBalooBlackList();
    Q_REQUIRED_RESULT QStringList cleanupEmailList(const QStringList &inputList);

    Q_REQUIRED_RESULT QStringList balooBlackList() const;
    Q_REQUIRED_RESULT QStringList domainExcludeList() const;

private:
    PimCommon::BalooCompletionEmail *const mBalooCompletionEmail;
    int mBalooCompletionSource = 0;
};
}
