/*
  SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

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
/*!
 * \class PimCommon::CustomToolsPluginManager
 * \brief The CustomToolsPluginManager class manages custom tools plugins
 * \inmodule PimCommon
 * \inheaderfile PimCommon/CustomToolsPluginManager
 * \author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT CustomToolsPluginManager : public QObject
{
    Q_OBJECT
public:
    /*!
     * Returns the singleton instance of CustomToolsPluginManager.
     * @return The singleton instance
     */
    static CustomToolsPluginManager *self();

    /*!
     * Constructs a CustomToolsPluginManager.
     * @param parent The parent QObject
     */
    explicit CustomToolsPluginManager(QObject *parent = nullptr);
    /*!
     * Destructs the CustomToolsPluginManager.
     */
    ~CustomToolsPluginManager() override;

    /*!
     * Returns the list of loaded custom tools plugins.
     * @return A list of CustomToolsPlugin instances
     */
    [[nodiscard]] QList<PimCommon::CustomToolsPlugin *> pluginsList() const;

private:
    std::unique_ptr<CustomToolsPluginManagerPrivate> const d;
};
}
