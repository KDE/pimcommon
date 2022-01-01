/*
  SPDX-FileCopyrightText: 2016-2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "abstractgenericplugin.h"

using namespace PimCommon;

AbstractGenericPlugin::AbstractGenericPlugin(QObject *parent)
    : QObject(parent)
{
}

AbstractGenericPlugin::~AbstractGenericPlugin() = default;

bool AbstractGenericPlugin::hasPopupMenuSupport() const
{
    return false;
}

bool AbstractGenericPlugin::hasToolBarSupport() const
{
    return false;
}

bool AbstractGenericPlugin::hasConfigureDialog() const
{
    return false;
}

bool AbstractGenericPlugin::hasStatusBarSupport() const
{
    return false;
}

void AbstractGenericPlugin::showConfigureDialog(QWidget *parent)
{
    Q_UNUSED(parent)
    // Reimplement it.
}

void AbstractGenericPlugin::setIsEnabled(bool enabled)
{
    mIsEnabled = enabled;
}

bool AbstractGenericPlugin::isEnabled() const
{
    return mIsEnabled;
}
