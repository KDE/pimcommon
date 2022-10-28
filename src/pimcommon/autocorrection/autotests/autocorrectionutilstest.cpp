/*
  SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "autocorrectionutilstest.h"
#include "autocorrection/autocorrectionutils.h"
#include <QTest>
QTEST_MAIN(AutoCorrectionUtilsTest)
AutoCorrectionUtilsTest::AutoCorrectionUtilsTest(QObject *parent)
    : QObject{parent}
{
}

void AutoCorrectionUtilsTest::shouldConvertToLibreOfficeFilename()
{
    QCOMPARE(PimCommon::AutoCorrectionUtils::libreofficeFile(QStringLiteral("Fr_fr")), QStringLiteral("acor_Fr_fr.dat"));
}
