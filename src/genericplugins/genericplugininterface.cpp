/*
  Copyright (c) 2015-2016 Montel Laurent <montel@kde.org>

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
        : plugin(Q_NULLPTR),
          parentWidget(Q_NULLPTR)
    {

    }
    ActionType actionType;
    GenericPlugin *plugin;
    QWidget *parentWidget;
};

GenericPluginInterface::GenericPluginInterface(QObject *parent)
    : QObject(parent),
      d(new GenericPluginInterfacePrivate)
{

}

GenericPluginInterface::~GenericPluginInterface()
{
    delete d;
}

void GenericPluginInterface::setParentWidget(QWidget *parent)
{
    d->parentWidget = parent;
}

QWidget *GenericPluginInterface::parentWidget() const
{
    return d->parentWidget;
}

void GenericPluginInterface::setActionType(const ActionType &type)
{
    d->actionType = type;
}

ActionType GenericPluginInterface::actionType() const
{
    return d->actionType;
}

void GenericPluginInterface::setPlugin(GenericPlugin *plugin)
{
    d->plugin = plugin;
}

GenericPlugin *GenericPluginInterface::plugin() const
{
    return d->plugin;
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

void GenericPluginInterface::showConfigureDialog(QWidget *parentWidget)
{
    Q_UNUSED(parentWidget);
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
