/*
   SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "addressesslineeditabstractplugin.h"

using namespace PimCommon;

AddressessLineEditAbstractPlugin::AddressessLineEditAbstractPlugin(QObject *parent)
    : QObject(parent)
{
}

AddressessLineEditAbstractPlugin::~AddressessLineEditAbstractPlugin()
{
}

void AddressessLineEditAbstractPlugin::setLineEdit(AddresseeLineEdit *linedit)
{
    mLinedit = linedit;
}
