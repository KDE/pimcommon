/*
  Copyright (c) 2016-2019 Montel Laurent <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "abstractgenericplugin.h"

using namespace PimCommon;

AbstractGenericPlugin::AbstractGenericPlugin(QObject *parent)
    : QObject(parent)
    , mIsEnabled(true)
{
}

AbstractGenericPlugin::~AbstractGenericPlugin()
{
}

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
    Q_UNUSED(parent);
    //Reimplement it.
}

void AbstractGenericPlugin::setIsEnabled(bool enabled)
{
    mIsEnabled = enabled;
}

bool AbstractGenericPlugin::isEnabled() const
{
    return mIsEnabled;
}
