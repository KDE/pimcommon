/*
   SPDX-FileCopyrightText: 2017-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "addressesslineeditabstractplugin.h"

using namespace PimCommon;

AddressessLineEditAbstractPlugin::AddressessLineEditAbstractPlugin(QObject *parent)
    : QObject(parent)
{
}

AddressessLineEditAbstractPlugin::~AddressessLineEditAbstractPlugin() = default;

#include "moc_addressesslineeditabstractplugin.cpp"
