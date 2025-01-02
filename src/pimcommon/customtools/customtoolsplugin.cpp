/*
  SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "customtoolsplugin.h"

using namespace PimCommon;

class PimCommon::CustomToolsPluginPrivate
{
public:
    bool enabled = false;
};

CustomToolsPlugin::CustomToolsPlugin(QObject *parent)
    : QObject(parent)
    , d(new PimCommon::CustomToolsPluginPrivate)
{
}

CustomToolsPlugin::~CustomToolsPlugin() = default;

bool CustomToolsPlugin::hasConfigureDialog() const
{
    return false;
}

void CustomToolsPlugin::showConfigureDialog(QWidget *parent)
{
    Q_UNUSED(parent)
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

#include "moc_customtoolsplugin.cpp"
