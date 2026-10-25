/*
   SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once
#include "pimcommonakonadi_private_export.h"
#include <QStringList>

namespace PimCommon::AddresseeLineUtil
{
/*!
 */
[[nodiscard]] PIMCOMMONAKONADI_TESTS_EXPORT QStringList excludeEmailsRegularExpression();
}
