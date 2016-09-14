/*
  Copyright (c) 2016 Montel Laurent <montel@kde.org>

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

#ifndef PLUGINUTIL_H
#define PLUGINUTIL_H

#include "pimcommon_export.h"

#include <QString>
#include <QStringList>
#include <QPair>
#include <kpluginmetadata.h>

namespace PimCommon
{

class PIMCOMMON_EXPORT PluginUtilData
{
public:
    PluginUtilData()
        : mEnableByDefault(false)
    {

    }
    QString mDescription;
    QString mIdentifier;
    QString mName;
    bool mEnableByDefault;
};

namespace PluginUtil
{
PIMCOMMON_EXPORT bool isPluginActivated(const QStringList &enabledPluginsList, const QStringList &disabledPluginsList, bool isEnabledByDefault, const QString &pluginId);
PIMCOMMON_EXPORT QPair<QStringList, QStringList> loadPluginSetting(const QString &groupName, const QString &prefixSettingKey);
PIMCOMMON_EXPORT void savePluginSettings(const QString &groupName, const QString &prefixSettingKey, const QStringList &enabledPluginsList, const QStringList &disabledPluginsList);
PIMCOMMON_EXPORT PimCommon::PluginUtilData createPluginMetaData(const KPluginMetaData &metaData);

}
}

#endif // PLUGINUTIL_H
