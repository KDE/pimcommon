/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "addresseelineutil.h"

using namespace Qt::Literals::StringLiterals;

QStringList PimCommon::AddresseeLineUtil::excludeEmailsRegularExpression()
{
    return {u"no.?reply.*@"_s, u"@noreply"_s};
}
