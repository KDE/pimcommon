/*
  SPDX-FileCopyrightText: 2014-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "contenttypewidgettest.h"
#include "../contenttypewidget.h"
#include <QComboBox>
#include <QLabel>
#include <QSignalSpy>
#include <QTest>
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
    auto label = widget.findChild<QLabel *>(QStringLiteral("contenttypewidgetlabel"));
    QVERIFY(label);
    auto combo = widget.findChild<QComboBox *>(QStringLiteral("contentcombobox"));
    QVERIFY(combo);
    QVERIFY(combo->count() > 0);
    QCOMPARE(widget.currentIndex(), 0);
}

void ContentTypeWidgetTest::shouldChangeComboBoxIndex()
{
    PimCommon::ContentTypeWidget contentType;
    auto combo = contentType.findChild<QComboBox *>(QStringLiteral("contentcombobox"));
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
    // FIXME
    // QCOMPARE(spy.at(0).count(), 1);
}

void ContentTypeWidgetTest::shouldChangeItem()
{
    PimCommon::ContentTypeWidget contentType;
    contentType.show();
    QVERIFY(QTest::qWaitForWindowExposed(&contentType));
    auto combo = contentType.findChild<QComboBox *>(QStringLiteral("contentcombobox"));
    for (int i = 0; i < combo->count(); ++i) {
        contentType.setCurrentIndex(i);
        QCOMPARE(contentType.currentText(), combo->currentText());
    }
}

QTEST_MAIN(ContentTypeWidgetTest)
