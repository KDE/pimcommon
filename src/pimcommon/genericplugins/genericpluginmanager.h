/*
  Copyright (c) 2015-2020 Laurent Montel <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef GENERICPLUGINMANAGER_H
#define GENERICPLUGINMANAGER_H

#include <QObject>
#include <QVector>
#include "pimcommon_export.h"
#include <PimCommon/PluginUtil>

namespace PimCommon {
class GenericPluginManagerPrivate;
class GenericPlugin;
/**
 * @brief The GenericPluginManager class
 * @author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT GenericPluginManager : public QObject
{
    Q_OBJECT
public:
    class GenericPluginData
    {
    public:
        GenericPluginData()
            : mEnableByDefault(false)
        {
        }

        QString mDescription;
        QString mName;
        QString mIdentifier;
        bool mEnableByDefault;
    };

    explicit GenericPluginManager(QObject *parent = nullptr);
    ~GenericPluginManager();

    Q_REQUIRED_RESULT bool initializePlugins();

    void setPluginDirectory(const QString &directory);
    Q_REQUIRED_RESULT QString pluginDirectory() const;

    void setPluginName(const QString &pluginName);
    Q_REQUIRED_RESULT QString pluginName() const;

    Q_REQUIRED_RESULT QVector<PimCommon::GenericPlugin *> pluginsList() const;
    Q_REQUIRED_RESULT QVector<PimCommon::PluginUtilData> pluginsDataList() const;

    Q_REQUIRED_RESULT QString configGroupName() const;
    Q_REQUIRED_RESULT QString configPrefixSettingKey() const;

    Q_REQUIRED_RESULT GenericPlugin *pluginFromIdentifier(const QString &id);

private:
    GenericPluginManagerPrivate *const d;
};
}

#endif // GENERICPLUGINMANAGER_H
