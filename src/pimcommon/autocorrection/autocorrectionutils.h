/*
  SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "autocorrection.h"

namespace AutoCorrectionUtils
{
Q_REQUIRED_RESULT PimCommon::AutoCorrection::TypographicQuotes typographicDefaultSingleQuotes();
Q_REQUIRED_RESULT PimCommon::AutoCorrection::TypographicQuotes typographicDefaultDoubleQuotes();

};
