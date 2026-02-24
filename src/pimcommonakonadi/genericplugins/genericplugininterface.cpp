/*
  SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "genericplugininterface.h"

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
}

void GenericPluginInterface::addActionType(ActionType type)
{
    if (!d->actionTypes.contains(type)) {
        d->actionTypes.append(type);
    }
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
