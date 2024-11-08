/*
  SPDX-FileCopyrightText: 2024 Laurent Montel <montel.org>

  SPDX-License-Identifier: GPL-2.0-or-later
  code based on kdenlive
*/

#include "verifynewversionutils.h"

#include <QUrl>
using namespace Qt::Literals::StringLiterals;
using namespace PimCommon;
bool VerifyNewVersionUtils::canVerifyNewVersion()
{
#if defined(Q_OS_WIN) || defined(Q_OS_MACOS)
    return true;
#endif
    return false;
}
