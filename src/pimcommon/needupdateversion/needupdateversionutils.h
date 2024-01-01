/*
  SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "pimcommon_export.h"
#include <QDate>
#include <QString>
namespace PimCommon
{
namespace NeedUpdateVersionUtils
{
enum class PIMCOMMON_EXPORT ObsoleteVersion {
    Unknown,
    NotObsoleteYet,
    OlderThan6Months,
    OlderThan12Months,
};

PIMCOMMON_EXPORT void disableCheckVersion();
PIMCOMMON_EXPORT bool checkVersion();
[[nodiscard]] PIMCOMMON_EXPORT NeedUpdateVersionUtils::ObsoleteVersion obsoleteVersionStatus(const QString &str, const QDate &currentDate);
};
}
