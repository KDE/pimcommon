/*
   SPDX-FileCopyrightText: 2017-2023 Laurent Montel <montel@kde.org>

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
/**
 * @brief The AddressessLineEditPluginManager class
 * @author Laurent Montel <montel@kde.org>
 */
class PIMCOMMONAKONADI_EXPORT AddressessLineEditPluginManager : public QObject
{
    Q_OBJECT
public:
    explicit AddressessLineEditPluginManager(QObject *parent = nullptr);
    ~AddressessLineEditPluginManager() override;

    static AddressessLineEditPluginManager *self();

    PimCommon::AddressessLineEditAbstractPlugin *plugin(const QString &identifier);
    QVector<PimCommon::AddressessLineEditAbstractPlugin *> pluginsList() const;

private:
    std::unique_ptr<AddressessLineEditPluginManagerPrivate> const d;
};
}
