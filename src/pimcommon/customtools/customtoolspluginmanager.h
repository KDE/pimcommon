/*
  SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef CUSTOMTOOLSPLUGINMANAGER_H
#define CUSTOMTOOLSPLUGINMANAGER_H

#include "pimcommon_export.h"
#include <QObject>
namespace PimCommon
{
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
    ~CustomToolsPluginManager() override;

    Q_REQUIRED_RESULT QVector<PimCommon::CustomToolsPlugin *> pluginsList() const;

private:
    CustomToolsPluginManagerPrivate *const d;
};
}
#endif // CUSTOMTOOLSPLUGINMANAGER_H
