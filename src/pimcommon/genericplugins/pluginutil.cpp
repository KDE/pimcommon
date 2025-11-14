/*
  SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "pluginutil.h"

QString PimCommon::PluginUtil::pluginConfigFile()
{
    return QStringLiteral("pimpluginsrc");
}

TextAddonsWidgets::PluginUtil::PluginsStateList PimCommon::PluginUtil::loadPluginSetting(const QString &groupName, const QString &prefixSettingKey)
{
    return TextAddonsWidgets::PluginUtil::loadPluginSetting(pluginConfigFile(), groupName, prefixSettingKey);
}
