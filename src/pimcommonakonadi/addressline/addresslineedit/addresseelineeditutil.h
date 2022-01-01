/*
   SPDX-FileCopyrightText: 2016-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "pimcommonakonadi_export.h"
#include <QString>

namespace PimCommon
{
/**
 * @brief The AddresseeLineEditUtil class
 * @author Laurent Montel <montel@kde.org>
 */
class PIMCOMMONAKONADI_EXPORT AddresseeLineEditUtil
{
public:
    static Q_REQUIRED_RESULT QString adaptPasteMails(const QString &str);
};
}

