/*
  Copyright (c) 2016-2017 Montel Laurent <montel@kde.org>

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

#include "abstractgenericplugininterface.h"

using namespace PimCommon;

class PimCommon::AbstractGenericPluginInterfacePrivate
{
public:
    AbstractGenericPluginInterfacePrivate()
        : plugin(Q_NULLPTR),
          parentWidget(Q_NULLPTR)
    {

    }
    AbstractGenericPlugin *plugin;
    QWidget *parentWidget;
};

AbstractGenericPluginInterface::AbstractGenericPluginInterface(QObject *parent)
    : QObject(parent),
      d(new AbstractGenericPluginInterfacePrivate)
{

}

AbstractGenericPluginInterface::~AbstractGenericPluginInterface()
{
    delete d;
}

void AbstractGenericPluginInterface::setParentWidget(QWidget *parent)
{
    d->parentWidget = parent;
}

QWidget *AbstractGenericPluginInterface::parentWidget() const
{
    return d->parentWidget;
}

void AbstractGenericPluginInterface::setPlugin(AbstractGenericPlugin *plugin)
{
    d->plugin = plugin;
}

AbstractGenericPlugin *AbstractGenericPluginInterface::plugin() const
{
    return d->plugin;
}

void AbstractGenericPluginInterface::showConfigureDialog(QWidget *parentWidget)
{
    Q_UNUSED(parentWidget);
}
