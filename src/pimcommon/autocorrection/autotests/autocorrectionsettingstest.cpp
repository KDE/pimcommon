/*
  SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "autocorrectionsettingstest.h"
#include "autocorrection/autocorrectionsettings.h"
#include <QTest>
QTEST_MAIN(AutoCorrectionSettingsTest)
AutoCorrectionSettingsTest::AutoCorrectionSettingsTest(QObject *parent)
    : QObject{parent}
{
}

void AutoCorrectionSettingsTest::shouldHaveDefaultValues()
{
    PimCommon::AutoCorrectionSettings settings;
    // TODO
}
