/*
  SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "autocorrectionutils.h"

PimCommon::AutoCorrection::TypographicQuotes AutoCorrectionUtils::typographicDefaultSingleQuotes()
{
    PimCommon::AutoCorrection::TypographicQuotes quote;
    quote.begin = QChar(0x2018);
    quote.end = QChar(0x2019);
    return quote;
}

PimCommon::AutoCorrection::TypographicQuotes AutoCorrectionUtils::typographicDefaultDoubleQuotes()
{
    PimCommon::AutoCorrection::TypographicQuotes quote;
    quote.begin = QChar(0x201c);
    quote.end = QChar(0x201d);
    return quote;
}
