/*
  SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "pimcommon_export.h"
#include <QObject>
#include <memory>
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

    [[nodiscard]] QList<PimCommon::CustomToolsPlugin *> pluginsList() const;

private:
    std::unique_ptr<CustomToolsPluginManagerPrivate> const d;
};
}
