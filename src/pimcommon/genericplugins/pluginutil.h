/*
  SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "pimcommon_export.h"

#include <KPluginMetaData>
#include <QPair>
#include <QString>
#include <QStringList>

namespace PimCommon
{
/**
 * @brief The PluginUtilData class
 * @author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT PluginUtilData
{
public:
    PluginUtilData() = default;

    QStringList mExtraInfo;
    QString mDescription;
    QString mIdentifier;
    QString mName;
    bool mEnableByDefault = false;
    bool mHasConfigureDialog = false;
};

namespace PluginUtil
{
[[nodiscard]] PIMCOMMON_EXPORT bool
isPluginActivated(const QStringList &enabledPluginsList, const QStringList &disabledPluginsList, bool isEnabledByDefault, const QString &pluginId);
[[nodiscard]] PIMCOMMON_EXPORT QPair<QStringList, QStringList> loadPluginSetting(const QString &groupName, const QString &prefixSettingKey);
PIMCOMMON_EXPORT void
savePluginSettings(const QString &groupName, const QString &prefixSettingKey, const QStringList &enabledPluginsList, const QStringList &disabledPluginsList);
[[nodiscard]] PIMCOMMON_EXPORT PimCommon::PluginUtilData createPluginMetaData(const KPluginMetaData &metaData);
}
}
