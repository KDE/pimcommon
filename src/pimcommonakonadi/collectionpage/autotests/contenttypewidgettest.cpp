/*
  Copyright (c) 2014-2020 Laurent Montel <montel@kde.org>

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

#include "contenttypewidgettest.h"
#include "../contenttypewidget.h"
#include <QComboBox>
#include <QLabel>
#include <QTest>
#include <QSignalSpy>
ContentTypeWidgetTest::ContentTypeWidgetTest(QObject *parent)
    : QObject(parent)
{
}

ContentTypeWidgetTest::~ContentTypeWidgetTest()
{
}

void ContentTypeWidgetTest::shouldHaveDefaultValue()
{
    PimCommon::ContentTypeWidget widget;
    QLabel *label = widget.findChild<QLabel *>(QStringLiteral("contenttypewidgetlabel"));
    QVERIFY(label);
    QComboBox *combo = widget.findChild<QComboBox *>(QStringLiteral("contentcombobox"));
    QVERIFY(combo);
    QVERIFY(combo->count() > 0);
    QCOMPARE(widget.currentIndex(), 0);
}

void ContentTypeWidgetTest::shouldChangeComboBoxIndex()
{
    PimCommon::ContentTypeWidget contentType;
    QComboBox *combo = contentType.findChild<QComboBox *>(QStringLiteral("contentcombobox"));
    for (int i = 0; i < combo->count(); ++i) {
        contentType.setCurrentIndex(i);
        QCOMPARE(contentType.currentIndex(), i);
        QCOMPARE(combo->currentIndex(), i);
    }
}

void ContentTypeWidgetTest::shouldEmitSignalWhenIndexChanged()
{
    PimCommon::ContentTypeWidget contentType;
    contentType.show();
    QVERIFY(QTest::qWaitForWindowExposed(&contentType));
    QSignalSpy spy(&contentType, &PimCommon::ContentTypeWidget::activated);
    contentType.setCurrentIndex(1);
    //FIXME
    //QCOMPARE(spy.at(0).count(), 1);
}

void ContentTypeWidgetTest::shouldChangeItem()
{
    PimCommon::ContentTypeWidget contentType;
    contentType.show();
    QVERIFY(QTest::qWaitForWindowExposed(&contentType));
    QComboBox *combo = contentType.findChild<QComboBox *>(QStringLiteral("contentcombobox"));
    for (int i = 0; i < combo->count(); ++i) {
        contentType.setCurrentIndex(i);
        QCOMPARE(contentType.currentText(), combo->currentText());
    }
}

QTEST_MAIN(ContentTypeWidgetTest)
