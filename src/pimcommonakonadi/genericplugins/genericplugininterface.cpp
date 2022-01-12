/*
  SPDX-FileCopyrightText: 2015-2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "genericplugininterface.h"

using namespace PimCommon;

class PimCommon::GenericPluginInterfacePrivate
{
public:
    GenericPluginInterfacePrivate() = default;

    QVector<ActionType> actionTypes;
};

GenericPluginInterface::GenericPluginInterface(QObject *parent)
    : AbstractGenericPluginInterface(parent)
    , d(new GenericPluginInterfacePrivate)
{
}

GenericPluginInterface::~GenericPluginInterface() = default;

void GenericPluginInterface::setActionTypes(const QVector<ActionType> &type)
{
    d->actionTypes = type;
}

void GenericPluginInterface::addActionType(ActionType type)
{
    // TODO check already existence ?
    d->actionTypes.append(type);
}

QVector<ActionType> GenericPluginInterface::actionTypes() const
{
    return d->actionTypes;
}

void GenericPluginInterface::updateActions(int numberOfSelectedItems, int numberOfSelectedCollections)
{
    Q_UNUSED(numberOfSelectedItems)
    Q_UNUSED(numberOfSelectedCollections)
}

void GenericPluginInterface::setCurrentItems(const Akonadi::Item::List &items)
{
    Q_UNUSED(items)
}

void GenericPluginInterface::setItems(const Akonadi::Item::List &items)
{
    Q_UNUSED(items)
}

void GenericPluginInterface::setCurrentCollection(const Akonadi::Collection &col)
{
    Q_UNUSED(col)
}

void GenericPluginInterface::setCollections(const Akonadi::Collection::List &cols)
{
    Q_UNUSED(cols)
}

PimCommon::GenericPluginInterface::RequireTypes GenericPluginInterface::requiresFeatures() const
{
    return None;
}

