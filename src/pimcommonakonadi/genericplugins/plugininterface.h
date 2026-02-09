/*
  SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "pimcommonakonadi_export.h"
#include <PimCommon/PluginUtil>
#include <PimCommonAkonadi/GenericPluginInterface>
#include <QObject>
#include <TextAddonsWidgets/PluginUtil>
class KActionCollection;
class QAction;
class KXMLGUIClient;
namespace PimCommon
{
class PluginInterfacePrivate;
/*!
 * \class PimCommon::PluginInterface
 * \brief The PluginInterface class manages Akonadi-aware generic plugins
 * \inmodule PimCommonAkonadi
 * \inheaderfile PimCommonAkonadi/PluginInterface
 * \author Laurent Montel <montel@kde.org>
 */
class PIMCOMMONAKONADI_EXPORT PluginInterface : public QObject
{
    Q_OBJECT
public:
    /*!
     * Constructs a PluginInterface.
     * @param parent The parent QObject
     */
    explicit PluginInterface(QObject *parent = nullptr);
    /*!
     * Destructs the PluginInterface.
     */
    ~PluginInterface() override;

    /*!
     * Sets the parent widget.
     * @param widget The widget to set as parent
     */
    void setParentWidget(QWidget *widget);
    /*!
     * Returns the actions organized by type.
     * @return A hash of action types to action lists
     */
    [[nodiscard]] QHash<PimCommon::ActionType::Type, QList<QAction *>> actionsType();
    /*!
     * Creates the plugin interface.
     */
    void createPluginInterface();

    /*!
     * Sets the plugin name filter.
     * @param name The plugin name
     */
    void setPluginName(const QString &name);
    /*!
     * Sets the directory containing plugins.
     * @param name The directory path
     */
    void setPluginDirectory(const QString &name);
    /*!
     * Initializes the plugins.
     */
    void initializePlugins();
    /*!
     * Initializes the interface requirements for a plugin.
     * @param interface The interface to initialize
     * @return true if initialization succeeded, false otherwise
     */
    virtual bool initializeInterfaceRequires(AbstractGenericPluginInterface *interface);
    /*!
     * Returns the XML extension for a given action type.
     * @param type The action type
     * @return The XML file extension
     */
    [[nodiscard]] static QString actionXmlExtension(PimCommon::ActionType::Type type);

    /*!
     * Initializes plugin actions.
     * @param prefix The prefix for action names
     * @param guiClient The KXMLGUIClient to add actions to
     */
    void initializePluginActions(const QString &prefix, KXMLGUIClient *guiClient);
    /*!
     * Updates actions based on selection state.
     * @param numberOfSelectedItems The number of selected items
     * @param numberOfSelectedCollections The number of selected collections
     */
    void updateActions(int numberOfSelectedItems, int numberOfSelectedCollections);

    /*!
     * Sets the action collection.
     * @param ac The KActionCollection
     */
    void setActionCollection(KActionCollection *ac);

    /*!
     * Returns the list of plugin data.
     * @return A list of PluginUtilData
     */
    [[nodiscard]] QList<TextAddonsWidgets::PluginUtilData> pluginsDataList() const;
    /*!
     * Returns the configuration group name.
     * @return The group name
     */
    [[nodiscard]] QString configGroupName() const;
    /*!
     * Returns the configuration prefix key.
     * @return The prefix key
     */
    [[nodiscard]] QString configPrefixSettingKey() const;

    /*!
     * Returns a plugin by its identifier.
     * @param id The plugin identifier
     * @return The GenericPlugin with the given id
     */
    [[nodiscard]] PimCommon::GenericPlugin *pluginFromIdentifier(const QString &id);
    /*!
     * Clears plugin actions.
     * @param prefix The prefix for action names
     * @param guiClient The KXMLGUIClient to remove actions from
     */
    void clearPluginActions(const QString &prefix, KXMLGUIClient *guiClient);

private:
    PIMCOMMONAKONADI_NO_EXPORT void slotPluginActivated(PimCommon::AbstractGenericPluginInterface *interface);
    std::unique_ptr<PluginInterfacePrivate> const d;
};
}
