/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef ADDRESSEELINEEDITUTIL_H
#define ADDRESSEELINEEDITUTIL_H

#include <QString>
#include "pimcommonakonadi_export.h"

namespace PimCommon {
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

#endif // ADDRESSEELINEEDITUTIL_H
