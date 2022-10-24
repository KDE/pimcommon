/*
  SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include <QChar>
namespace PimCommon
{
namespace AutoCorrectionUtils
{
struct TypographicQuotes {
    QChar begin;
    QChar end;
};

Q_REQUIRED_RESULT TypographicQuotes typographicDefaultSingleQuotes();
Q_REQUIRED_RESULT TypographicQuotes typographicDefaultDoubleQuotes();
};
}
