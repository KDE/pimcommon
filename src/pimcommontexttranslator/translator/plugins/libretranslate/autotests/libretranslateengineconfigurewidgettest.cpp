/*
  SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "libretranslateengineconfigurewidgettest.h"
#include "../libretranslateengineconfigurewidget.h"
#include <QTest>
QTEST_MAIN(LibreTranslateEngineConfigureWidgetTest)
LibreTranslateEngineConfigureWidgetTest::LibreTranslateEngineConfigureWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void LibreTranslateEngineConfigureWidgetTest::shouldHaveDefaultValues()
{
    LibreTranslateEngineConfigureWidget w;
    // TODO
}
