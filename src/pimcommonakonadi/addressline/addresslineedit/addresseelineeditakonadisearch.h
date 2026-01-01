/*
   SPDX-FileCopyrightText: 2017-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once
#include "pimcommonakonadi_private_export.h"
#include <QStringList>

namespace PimCommon
{
class AkonadiSearchCompletionEmail;
class PIMCOMMONAKONADI_TESTS_EXPORT AddresseeLineEditAkonadiSearch
{
public:
    AddresseeLineEditAkonadiSearch();
    ~AddresseeLineEditAkonadiSearch();

    [[nodiscard]] int akonadiSearchCompletionSource() const;
    void setAkonadiSearchCompletionSource(int value);
    void loadAkonadiSearchBlackList();
    [[nodiscard]] QStringList cleanupEmailList(const QStringList &inputList);

    [[nodiscard]] QStringList akonadiSearchBlackList() const;
    [[nodiscard]] QStringList domainExcludeList() const;

private:
    PimCommon::AkonadiSearchCompletionEmail *const mAkonadiSearchCompletionEmail;
    int mAkonadiSearchCompletionSource = 0;
};
}
