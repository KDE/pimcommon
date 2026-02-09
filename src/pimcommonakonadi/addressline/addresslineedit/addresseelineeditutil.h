/*
   SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "pimcommonakonadi_export.h"
#include <QString>

namespace PimCommon
{
/*!
 * \class PimCommon::AddresseeLineEditUtil
 * \brief The AddresseeLineEditUtil class provides utility functions for addressee line editing
 * \inmodule PimCommonAkonadi
 * \inheaderfile PimCommonAkonadi/AddresseeLineEditUtil
 * \author Laurent Montel <montel@kde.org>
 */
class PIMCOMMONAKONADI_EXPORT AddresseeLineEditUtil
{
public:
    /*!
     * Adapts pasted email addresses for use in the addressee line editor.
     * @param str The pasted text
     * @return The adapted email address text
     */
    [[nodiscard]] static QString adaptPasteMails(const QString &str);
};
}
