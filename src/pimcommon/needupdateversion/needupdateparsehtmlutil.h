/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "pimcommon_export.h"
#include <QString>
namespace PimCommon
{
namespace NeedUpdateParseHtmlUtil
{
[[nodiscard]] PIMCOMMON_EXPORT QString extractDate(const QString &dataHtml);
};
}
