/*
    SPDX-FileCopyrightText: 2024 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "addresseeactivitiesabstract.h"
using namespace PimCommon;
AddresseeActivitiesAbstract::AddresseeActivitiesAbstract(QObject *parent)
    : QObject{parent}
{
}

AddresseeActivitiesAbstract::~AddresseeActivitiesAbstract() = default;

#include "moc_addresseeactivitiesabstract.cpp"
