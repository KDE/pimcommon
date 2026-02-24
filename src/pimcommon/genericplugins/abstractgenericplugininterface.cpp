/*
  SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "abstractgenericplugininterface.h"

using namespace PimCommon;

class PimCommon::AbstractGenericPluginInterfacePrivate
{
public:
    AbstractGenericPluginInterfacePrivate() = default;

    AbstractGenericPlugin *plugin = nullptr;
    QWidget *parentWidget = nullptr;
};

AbstractGenericPluginInterface::AbstractGenericPluginInterface(QObject *parent)
    : QObject(parent)
    , d(new AbstractGenericPluginInterfacePrivate)
{
}

AbstractGenericPluginInterface::~AbstractGenericPluginInterface() = default;

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

void AbstractGenericPluginInterface::showConfigureDialog([[maybe_unused]] QWidget *parentWidget)
{
}

ActionType::ActionType(QAction *action, ActionType::Type type)
    : mAction(action)
    , mType(type)
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

bool ActionType::operator==(ActionType other) const
{
    return mAction == other.mAction && mType == other.mType;
}

#include "moc_abstractgenericplugininterface.cpp"
