/*
  Copyright (c) 2016-2018 Montel Laurent <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License, version 2, as
  published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "pluginutil.h"
#include <KConfigGroup>
#include <KSharedConfig>

namespace {
inline QString pluginConfigFile()
{
    return QStringLiteral("pimpluginsrc");
}
}

bool PimCommon::PluginUtil::isPluginActivated(const QStringList &enabledPluginsList, const QStringList &disabledPluginsList, bool isEnabledByDefault, const QString &pluginId)
{
    if (pluginId.isEmpty()) {
        return false;
    }
    const bool pluginEnabledByUser = enabledPluginsList.contains(pluginId);
    const bool pluginDisabledByUser = disabledPluginsList.contains(pluginId);
    if ((isEnabledByDefault && !pluginDisabledByUser)
        || (!isEnabledByDefault && pluginEnabledByUser)) {
        return true;
    }
    return false;
}

QPair<QStringList, QStringList> PimCommon::PluginUtil::loadPluginSetting(const QString &groupName, const QString &prefixSettingKey)
{
    QPair<QStringList, QStringList> pair;
    KSharedConfigPtr config = KSharedConfig::openConfig(pluginConfigFile());
    QStringList enabledPlugins;
    QStringList disabledPlugins;
    if (config->hasGroup(groupName)) {
        KConfigGroup grp = config->group(groupName);
        enabledPlugins = grp.readEntry(QStringLiteral("%1Enabled").arg(prefixSettingKey), QStringList());
        disabledPlugins = grp.readEntry(QStringLiteral("%1Disabled").arg(prefixSettingKey), QStringList());
    }

    pair.first = enabledPlugins;
    pair.second = disabledPlugins;
    return pair;
}

void PimCommon::PluginUtil::savePluginSettings(const QString &groupName, const QString &prefixSettingKey, const QStringList &enabledPluginsList, const QStringList &disabledPluginsList)
{
    KSharedConfigPtr config = KSharedConfig::openConfig(pluginConfigFile());
    KConfigGroup grp = config->group(groupName);
    grp.writeEntry(QStringLiteral("%1Enabled").arg(prefixSettingKey), enabledPluginsList);
    grp.writeEntry(QStringLiteral("%1Disabled").arg(prefixSettingKey), disabledPluginsList);
}

PimCommon::PluginUtilData PimCommon::PluginUtil::createPluginMetaData(const KPluginMetaData &metaData)
{
    PluginUtilData pluginData;
    pluginData.mDescription = metaData.description();
    pluginData.mName = metaData.name();
    pluginData.mIdentifier = metaData.pluginId();
    pluginData.mEnableByDefault = metaData.isEnabledByDefault();
    return pluginData;
}
