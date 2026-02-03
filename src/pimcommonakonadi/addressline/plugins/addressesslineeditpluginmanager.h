/*
   SPDX-FileCopyrightText: 2017-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "pimcommonakonadi_export.h"
#include <QObject>
#include <memory>

namespace PimCommon
{
class AddressessLineEditAbstractPlugin;
class AddressessLineEditPluginManagerPrivate;
/*!
 * \class AddressessLineEditPluginManager
 * \brief The AddressessLineEditPluginManager class manages addressee line edit plugins
 * \inmodule PimCommonAkonadi
 * \inheaderfile PimCommonAkonadi/AddressessLineEditPluginManager
 * \author Laurent Montel <montel@kde.org>
 */
class PIMCOMMONAKONADI_EXPORT AddressessLineEditPluginManager : public QObject
{
    Q_OBJECT
public:
    /*!
     * Constructs an AddressessLineEditPluginManager.
     * @param parent The parent QObject
     */
    explicit AddressessLineEditPluginManager(QObject *parent = nullptr);
    /*!
     * Destructs the AddressessLineEditPluginManager.
     */
    ~AddressessLineEditPluginManager() override;

    /*!
     * Returns the singleton instance of AddressessLineEditPluginManager.
     * @return The singleton instance
     */
    static AddressessLineEditPluginManager *self();

    /*!
     * Returns a plugin by its identifier.
     * @param identifier The plugin identifier
     * @return The AddressessLineEditAbstractPlugin with the given identifier
     */
    [[nodiscard]] PimCommon::AddressessLineEditAbstractPlugin *plugin(const QString &identifier);
    /*!
     * Returns the list of all available plugins.
     * @return A list of AddressessLineEditAbstractPlugin instances
     */
    [[nodiscard]] QList<PimCommon::AddressessLineEditAbstractPlugin *> pluginsList() const;

private:
    std::unique_ptr<AddressessLineEditPluginManagerPrivate> const d;
};
}
