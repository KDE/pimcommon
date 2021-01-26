/*
  SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "pluginutil.h"
#include <KConfigGroup>
#include <KSharedConfig>

namespace
{
inline QString pluginConfigFile()
{
    return QStringLiteral("pimpluginsrc");
}
}

bool PimCommon::PluginUtil::isPluginActivated(const QStringList &enabledPluginsList,
                                              const QStringList &disabledPluginsList,
                                              bool isEnabledByDefault,
                                              const QString &pluginId)
{
    if (pluginId.isEmpty()) {
        return false;
    }
    const bool pluginEnabledByUser = enabledPluginsList.contains(pluginId);
    const bool pluginDisabledByUser = disabledPluginsList.contains(pluginId);
    if ((isEnabledByDefault && !pluginDisabledByUser) || (!isEnabledByDefault && pluginEnabledByUser)) {
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

void PimCommon::PluginUtil::savePluginSettings(const QString &groupName,
                                               const QString &prefixSettingKey,
                                               const QStringList &enabledPluginsList,
                                               const QStringList &disabledPluginsList)
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
