/*
  SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "libretranslateengineutil.h"

QString PimCommonTextTranslator::LibreTranslateEngineUtil::groupName()
{
    return QStringLiteral("LibreTranslateTranslator");
}

QString PimCommonTextTranslator::LibreTranslateEngineUtil::serverUrlKey()
{
    return QStringLiteral("ServerUrl");
}
