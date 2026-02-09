/*
  SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "pimcommon_export.h"
#include <PimCommon/PluginUtil>
#include <QList>
#include <QObject>
#include <TextAddonsWidgets/PluginUtil>

namespace PimCommon
{
class GenericPluginManagerPrivate;
class GenericPlugin;
/*!
 * \class PimCommon::GenericPluginManager
 * \brief The GenericPluginManager class manages generic plugins
 * \inmodule PimCommon
 * \inheaderfile PimCommon/GenericPluginManager
 * \author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT GenericPluginManager : public QObject
{
    Q_OBJECT
public:
    /*!
     * Contains data about a generic plugin.
     */
    class GenericPluginData
    {
    public:
        GenericPluginData() = default;

        QString mDescription;
        QString mName;
        QString mIdentifier;
        bool mEnableByDefault = false;
    };

    /*!
     * Constructs a GenericPluginManager.
     * @param parent The parent QObject
     */
    explicit GenericPluginManager(QObject *parent = nullptr);
    /*!
     * Destructs the GenericPluginManager.
     */
    ~GenericPluginManager() override;

    /*!
     * Initializes the plugins.
     * @return true if initialization was successful, false otherwise
     */
    [[nodiscard]] bool initializePlugins();

    /*!
     * Sets the directory where plugins are located.
     * @param directory The plugin directory path
     */
    void setPluginDirectory(const QString &directory);
    /*!
     * Returns the plugin directory.
     * @return The plugin directory path
     */
    [[nodiscard]] QString pluginDirectory() const;

    /*!
     * Sets the plugin name filter.
     * @param pluginName The plugin name to filter by
     */
    void setPluginName(const QString &pluginName);
    /*!
     * Returns the plugin name filter.
     * @return The plugin name filter
     */
    [[nodiscard]] QString pluginName() const;

    /*!
     * Returns the list of loaded plugins.
     * @return A list of GenericPlugin instances
     */
    [[nodiscard]] QList<PimCommon::GenericPlugin *> pluginsList() const;
    /*!
     * Returns the data list of plugins.
     * @return A list of PluginUtilData for all plugins
     */
    [[nodiscard]] QList<TextAddonsWidgets::PluginUtilData> pluginsDataList() const;

    /*!
     * Returns the configuration group name.
     * @return The configuration group name
     */
    [[nodiscard]] QString configGroupName() const;
    /*!
     * Returns the configuration prefix setting key.
     * @return The configuration prefix key
     */
    [[nodiscard]] QString configPrefixSettingKey() const;

    /*!
     * Returns a plugin by its identifier.
     * @param id The plugin identifier
     * @return The GenericPlugin with the given id, or nullptr if not found
     */
    [[nodiscard]] GenericPlugin *pluginFromIdentifier(const QString &id);

private:
    std::unique_ptr<GenericPluginManagerPrivate> const d;
};
}
