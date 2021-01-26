/*
  SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef PLUGINUTIL_H
#define PLUGINUTIL_H

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
    PluginUtilData()
        : mEnableByDefault(false)
        , mHasConfigureDialog(false)
    {
    }

    QStringList mExtraInfo;
    QString mDescription;
    QString mIdentifier;
    QString mName;
    bool mEnableByDefault;
    bool mHasConfigureDialog;
};

namespace PluginUtil
{
Q_REQUIRED_RESULT PIMCOMMON_EXPORT bool
isPluginActivated(const QStringList &enabledPluginsList, const QStringList &disabledPluginsList, bool isEnabledByDefault, const QString &pluginId);
Q_REQUIRED_RESULT PIMCOMMON_EXPORT QPair<QStringList, QStringList> loadPluginSetting(const QString &groupName, const QString &prefixSettingKey);
PIMCOMMON_EXPORT void
savePluginSettings(const QString &groupName, const QString &prefixSettingKey, const QStringList &enabledPluginsList, const QStringList &disabledPluginsList);
Q_REQUIRED_RESULT PIMCOMMON_EXPORT PimCommon::PluginUtilData createPluginMetaData(const KPluginMetaData &metaData);
}
}

#endif // PLUGINUTIL_H
