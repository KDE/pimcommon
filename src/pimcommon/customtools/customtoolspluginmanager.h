/*
  Copyright (c) 2015-2019 Montel Laurent <montel@kde.org>

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

#ifndef CUSTOMTOOLSPLUGINMANAGER_H
#define CUSTOMTOOLSPLUGINMANAGER_H

#include <QObject>
#include "pimcommon_export.h"
namespace PimCommon {
class CustomToolsPlugin;
class CustomToolsPluginManagerPrivate;
/**
 * @brief The CustomToolsPluginManager class
 * @author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT CustomToolsPluginManager : public QObject
{
    Q_OBJECT
public:
    static CustomToolsPluginManager *self();

    explicit CustomToolsPluginManager(QObject *parent = nullptr);
    ~CustomToolsPluginManager();

    Q_REQUIRED_RESULT QVector<PimCommon::CustomToolsPlugin *> pluginsList() const;
private:
    CustomToolsPluginManagerPrivate *const d;
};
}
#endif // CUSTOMTOOLSPLUGINMANAGER_H
