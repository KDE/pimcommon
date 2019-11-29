/*
  Copyright (c) 2014-2019 Montel Laurent <montel@kde.org>

  This library is free software; you can redistribute it and/or modify it
  under the terms of the GNU Library General Public License as published by
  the Free Software Foundation; either version 2 of the License, or (at your
  option) any later version.

  This library is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
  License for more details.

  You should have received a copy of the GNU Library General Public License
  along with this library; see the file COPYING.LIB.  If not, write to the
  Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
  02110-1301, USA.

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
    QLabel *label = contentType.findChild<QLabel *>(QStringLiteral("contentstypelabel"));
    QVERIFY(label);
    QComboBox *combo = contentType.findChild<QComboBox *>(QStringLiteral("contentstypecombobox"));
    QVERIFY(combo);
    QVERIFY(combo->count() > 0);
    QCOMPARE(contentType.currentIndex(), 0);
}

void IncidencesForWidgetTest::shouldChangeComboBoxIndex()
{
    PimCommon::IncidencesForWidget contentType;
    QComboBox *combo = contentType.findChild<QComboBox *>(QStringLiteral("contentstypecombobox"));
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
