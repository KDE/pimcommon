/*
  SPDX-FileCopyrightText: 2014-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "incidencesforwidgettest.h"
#include "../incidencesforwidget.h"
#include <QComboBox>
#include <QLabel>
#include <QTest>
#include <QSignalSpy>

IncidencesForWidgetTest::IncidencesForWidgetTest(QObject *parent)
    : QObject(parent)
{
}

IncidencesForWidgetTest::~IncidencesForWidgetTest()
{
}

void IncidencesForWidgetTest::shouldHaveDefaultValue()
{
    PimCommon::IncidencesForWidget contentType;
    auto *label = contentType.findChild<QLabel *>(QStringLiteral("contentstypelabel"));
    QVERIFY(label);
    auto *combo = contentType.findChild<QComboBox *>(QStringLiteral("contentstypecombobox"));
    QVERIFY(combo);
    QVERIFY(combo->count() > 0);
    QCOMPARE(contentType.currentIndex(), 0);
}

void IncidencesForWidgetTest::shouldChangeComboBoxIndex()
{
    PimCommon::IncidencesForWidget contentType;
    auto *combo = contentType.findChild<QComboBox *>(QStringLiteral("contentstypecombobox"));
    for (int i = 0; i < combo->count(); ++i) {
        contentType.setCurrentIndex(i);
        QCOMPARE(contentType.currentIndex(), i);
        QCOMPARE(combo->currentIndex(), i);
    }
}

void IncidencesForWidgetTest::shouldEmitSignalWhenIndexChanged()
{
    PimCommon::IncidencesForWidget contentType;
    contentType.show();
    QVERIFY(QTest::qWaitForWindowExposed(&contentType));
    QSignalSpy spy(&contentType, &PimCommon::IncidencesForWidget::currentIndexChanged);
    contentType.setCurrentIndex(1);
    QCOMPARE(spy.at(0).count(), 1);
}

QTEST_MAIN(IncidencesForWidgetTest)
