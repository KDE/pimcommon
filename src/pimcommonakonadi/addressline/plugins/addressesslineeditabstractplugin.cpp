/*
   SPDX-FileCopyrightText: 2017-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "addressesslineeditabstractplugin.h"

using namespace PimCommon;

AddressessLineEditAbstractPlugin::AddressessLineEditAbstractPlugin(QObject *parent)
    : QObject(parent)
{
}

AddressessLineEditAbstractPlugin::~AddressessLineEditAbstractPlugin() = default;

void AddressessLineEditAbstractPlugin::setLineEdit(AddresseeLineEdit *linedit)
{
    mLinedit = linedit;
}

#include "moc_addressesslineeditabstractplugin.cpp"
