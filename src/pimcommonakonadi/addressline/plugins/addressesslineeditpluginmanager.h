/*
   SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef ADDRESSESSLINEEDITPLUGINMANAGER_H
#define ADDRESSESSLINEEDITPLUGINMANAGER_H

#include <QObject>
#include "pimcommonakonadi_export.h"

namespace PimCommon {
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
    ~AddressessLineEditPluginManager();

    static AddressessLineEditPluginManager *self();

    PimCommon::AddressessLineEditAbstractPlugin *plugin(const QString &identifier);
    QVector<PimCommon::AddressessLineEditAbstractPlugin *> pluginsList() const;

private:
    AddressessLineEditPluginManagerPrivate *const d;
};
}

#endif // ADDRESSESSLINEEDITPLUGINMANAGER_H