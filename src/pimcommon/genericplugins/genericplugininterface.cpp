/*
  Copyright (c) 2015-2017 Montel Laurent <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License, version 2, as
  published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "genericplugininterface.h"

using namespace PimCommon;

class PimCommon::GenericPluginInterfacePrivate
{
public:
    GenericPluginInterfacePrivate()
    {

    }
    ActionType actionType;
};

GenericPluginInterface::GenericPluginInterface(QObject *parent)
    : AbstractGenericPluginInterface(parent),
      d(new GenericPluginInterfacePrivate)
{

}

GenericPluginInterface::~GenericPluginInterface()
{
    delete d;
}

void GenericPluginInterface::setActionType(const ActionType &type)
{
    d->actionType = type;
}

ActionType GenericPluginInterface::actionType() const
{
    return d->actionType;
}

void GenericPluginInterface::updateActions(int numberOfSelectedItems, int numberOfSelectedCollections)
{
    Q_UNUSED(numberOfSelectedItems);
    Q_UNUSED(numberOfSelectedCollections);
}

void GenericPluginInterface::setCurrentItems(const Akonadi::Item::List &items)
{
    Q_UNUSED(items);
}

void GenericPluginInterface::setItems(const Akonadi::Item::List &items)
{
    Q_UNUSED(items);
}

void GenericPluginInterface::setCurrentCollection(const Akonadi::Collection &col)
{
    Q_UNUSED(col);
}

void GenericPluginInterface::setCollections(const Akonadi::Collection::List &cols)
{
    Q_UNUSED(cols);
}

PimCommon::GenericPluginInterface::RequireTypes GenericPluginInterface::requires() const
{
    return None;
}

ActionType::ActionType(QAction *action, ActionType::Type type)
    : mAction(action),
      mType(type)
{
}

QAction *ActionType::action() const
{
    return mAction;
}

ActionType::Type ActionType::type() const
{
    return mType;
}
