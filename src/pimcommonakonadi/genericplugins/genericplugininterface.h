/*
  SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "pimcommonakonadi_export.h"
#include <Akonadi/Item>
#include <PimCommon/AbstractGenericPluginInterface>

namespace PimCommon
{
class GenericPluginInterfacePrivate;
/*!
 * \class GenericPluginInterface
 * \brief The GenericPluginInterface class provides an Akonadi-aware generic plugin interface
 * \inmodule PimCommonAkonadi
 * \inheaderfile PimCommonAkonadi/GenericPluginInterface
 * \author Laurent Montel <montel@kde.org>
 */
class PIMCOMMONAKONADI_EXPORT GenericPluginInterface : public AbstractGenericPluginInterface
{
    Q_OBJECT
public:
    /*!
     * Constructs a GenericPluginInterface.
     * @param parent The parent QObject
     */
    explicit GenericPluginInterface(QObject *parent = nullptr);
    /*!
     * Destructs the GenericPluginInterface.
     */
    ~GenericPluginInterface() override;

    enum RequireType {
        None = 0,
        CurrentItems = 1,
        Items = 2,
        CurrentCollection = 3,
        Collections = 4,
    };
    Q_ENUM(RequireType)
    Q_DECLARE_FLAGS(RequireTypes, RequireType)

    /*!
     * Sets the action types for this plugin.
     * @param type The list of action types
     */
    void setActionTypes(const QList<ActionType> &type);
    /*!
     * Adds an action type to this plugin.
     * @param type The action type to add
     */
    void addActionType(ActionType type);
    /*!
     * Returns the list of action types.
     * @return The action types
     */
    [[nodiscard]] QList<ActionType> actionTypes() const;

    /*!
     * Sets the current items for this plugin.
     * @param items The list of current Akonadi items
     */
    virtual void setCurrentItems(const Akonadi::Item::List &items);
    /*!
     * Sets the items for this plugin.
     * @param items The list of Akonadi items
     */
    virtual void setItems(const Akonadi::Item::List &items);
    /*!
     * Sets the current collection for this plugin.
     * @param col The current Akonadi collection
     */
    virtual void setCurrentCollection(const Akonadi::Collection &col);
    /*!
     * Sets the collections for this plugin.
     * @param cols The list of Akonadi collections
     */
    virtual void setCollections(const Akonadi::Collection::List &cols);

    /*!
     * Returns the required features for this plugin.
     * @return The required features as RequireTypes
     */
    virtual GenericPluginInterface::RequireTypes requiresFeatures() const;

    /*!
     * Updates actions based on selection state.
     * @param numberOfSelectedItems The number of selected items
     * @param numberOfSelectedCollections The number of selected collections
     */
    virtual void updateActions(int numberOfSelectedItems, int numberOfSelectedCollections);

private:
    std::unique_ptr<GenericPluginInterfacePrivate> const d;
};
}
Q_DECLARE_TYPEINFO(PimCommon::ActionType, Q_RELOCATABLE_TYPE);
