/*
  SPDX-FileCopyrightText: 2014-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "incidencesforwidgettest.h"
#include "../incidencesforwidget.h"
#include <QTest>

IncidencesForWidgetTest::IncidencesForWidgetTest(QObject *parent)
    : QObject(parent)
{
}

IncidencesForWidgetTest::~IncidencesForWidgetTest() = default;

void IncidencesForWidgetTest::shouldHaveDefaultValue()
{
    PimCommon::IncidencesForWidget contentType;
    QVERIFY(contentType.count() == 3);
    QCOMPARE(contentType.currentIndex(), 0);
}

QTEST_MAIN(IncidencesForWidgetTest)
