/*
  Copyright (c) 2015-2020 Laurent Montel <montel@kde.org>

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

#include "customtoolsplugin.h"

using namespace PimCommon;

class PimCommon::CustomToolsPluginPrivate
{
public:
    CustomToolsPluginPrivate()
    {
    }

    bool enabled = false;
};

CustomToolsPlugin::CustomToolsPlugin(QObject *parent)
    : QObject(parent)
    , d(new PimCommon::CustomToolsPluginPrivate)
{
}

CustomToolsPlugin::~CustomToolsPlugin()
{
    delete d;
}

bool CustomToolsPlugin::hasConfigureDialog() const
{
    return false;
}

void CustomToolsPlugin::showConfigureDialog(QWidget *parent)
{
    Q_UNUSED(parent);
}

QString CustomToolsPlugin::description() const
{
    return {};
}

void CustomToolsPlugin::setIsEnabled(bool enabled)
{
    d->enabled = enabled;
}

bool CustomToolsPlugin::isEnabled() const
{
    return d->enabled;
}
