/*
    SPDX-FileCopyrightText: 2024 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "pimcommonakonadi_export.h"
#include <QObject>
namespace PimCommon
{
class PIMCOMMONAKONADI_EXPORT AddresseeActivitiesAbstract : public QObject
{
    Q_OBJECT
public:
    explicit AddresseeActivitiesAbstract(QObject *parent = nullptr);
    ~AddresseeActivitiesAbstract() override;
};
}
