/*
  SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "genericplugin.h"

using namespace PimCommon;

GenericPlugin::GenericPlugin(QObject *parent)
    : AbstractGenericPlugin(parent)
{
}

GenericPlugin::~GenericPlugin() = default;

#include "moc_genericplugin.cpp"
