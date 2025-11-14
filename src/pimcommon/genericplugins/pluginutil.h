/*
  SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "pimcommon_export.h"
#include <QString>
#include <TextAddonsWidgets/PluginUtil>
namespace PimCommon
{
namespace PluginUtil
{
PIMCOMMON_EXPORT QString pluginConfigFile();
PIMCOMMON_EXPORT TextAddonsWidgets::PluginUtil::PluginsStateList loadPluginSetting(const QString &groupName, const QString &prefixSettingKey);
}
}
