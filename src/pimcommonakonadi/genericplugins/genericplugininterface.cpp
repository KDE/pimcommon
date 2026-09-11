/*
  SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "genericplugininterface.h"

#include <QAction>

using namespace PimCommon;

class PimCommon::GenericPluginInterfacePrivate
{
public:
    GenericPluginInterfacePrivate() = default;

    QList<ActionType> actionTypes;
};

GenericPluginInterface::GenericPluginInterface(QObject *parent)
    : AbstractGenericPluginInterface(parent)
    , d(new GenericPluginInterfacePrivate)
{
}

GenericPluginInterface::~GenericPluginInterface() = default;

void GenericPluginInterface::setActionTypes(const QList<ActionType> &type)
{
    d->actionTypes = type;
    for (const ActionType &actionType : type) {
        watchActionDestroyed(actionType.action());
    }
}

void GenericPluginInterface::addActionType(ActionType type)
{
    if (!d->actionTypes.contains(type)) {
        d->actionTypes.append(type);
        watchActionDestroyed(type.action());
    }
}

void GenericPluginInterface::watchActionDestroyed(QAction *action)
{
    if (!action) {
        return;
    }
    connect(action, &QObject::destroyed, this, [this, action]() {
        d->actionTypes.removeIf([action](const ActionType &actionType) {
            return actionType.action() == action;
        });
    });
}

QList<ActionType> GenericPluginInterface::actionTypes() const
{
    return d->actionTypes;
}

void GenericPluginInterface::updateActions([[maybe_unused]] int numberOfSelectedItems, [[maybe_unused]] int numberOfSelectedCollections)
{
}

void GenericPluginInterface::setCurrentItems([[maybe_unused]] const Akonadi::Item::List &items)
{
}

void GenericPluginInterface::setItems([[maybe_unused]] const Akonadi::Item::List &items)
{
}

void GenericPluginInterface::setCurrentCollection([[maybe_unused]] const Akonadi::Collection &col)
{
}

void GenericPluginInterface::setCollections([[maybe_unused]] const Akonadi::Collection::List &cols)
{
}

PimCommon::GenericPluginInterface::RequireTypes GenericPluginInterface::requiresFeatures() const
{
    return None;
}

#include "moc_genericplugininterface.cpp"
