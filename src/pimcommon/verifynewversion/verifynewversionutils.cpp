/*
  SPDX-FileCopyrightText: 2024 Laurent Montel <montel.org>

  SPDX-License-Identifier: GPL-2.0-or-later
  code based on kdenlive
*/

#include "verifynewversionutils.h"

#include <QUrl>
using namespace Qt::Literals::StringLiterals;
using namespace PimCommon;
QUrl VerifyNewVersionUtils::newVersionUrl()
{
#if defined(Q_OS_WIN)
    return QUrl("https://cdn.kde.org/ci-builds/network/ruqola/master/windows/"_L1);
#endif

#if defined(Q_OS_MACOS)
#ifdef Q_PROCESSOR_ARM_64
    return QUrl("https://cdn.kde.org/ci-builds/network/ruqola/master/macos-arm64/"_L1);
#else
    return QUrl("https://cdn.kde.org/ci-builds/network/ruqola/master/macos-x86_64/"_L1);
#endif
#endif
    return {};
}

bool VerifyNewVersionUtils::canVerifyNewVersion()
{
#if defined(Q_OS_WIN) || defined(Q_OS_MACOS)
    return true;
#endif
    return false;
}
