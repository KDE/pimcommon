/*
  SPDX-FileCopyrightText: 2024 Laurent Montel <montel.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "pimcommon_export.h"
#include <QString>
#include <QUrl>

namespace PimCommon
{
namespace VerifyNewVersionUtils
{
[[nodiscard]] PIMCOMMON_EXPORT bool checkVersion();
[[nodiscard]] PIMCOMMON_EXPORT QUrl newVersionUrl();
[[nodiscard]] PIMCOMMON_EXPORT bool canVerifyNewVersion();
};
}
