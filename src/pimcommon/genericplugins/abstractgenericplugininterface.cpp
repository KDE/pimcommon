/*
  SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "abstractgenericplugininterface.h"

using namespace PimCommon;

class PimCommon::AbstractGenericPluginInterfacePrivate
{
public:
    AbstractGenericPluginInterfacePrivate()
    {
    }

    AbstractGenericPlugin *plugin = nullptr;
    QWidget *parentWidget = nullptr;
};

AbstractGenericPluginInterface::AbstractGenericPluginInterface(QObject *parent)
    : QObject(parent)
    , d(new AbstractGenericPluginInterfacePrivate)
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
