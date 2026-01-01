/*
  SPDX-FileCopyrightText: 2014-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "contenttypewidgettest.h"
#include "../contenttypewidget.h"
#include <QTest>
ContentTypeWidgetTest::ContentTypeWidgetTest(QObject *parent)
    : QObject(parent)
{
}

ContentTypeWidgetTest::~ContentTypeWidgetTest() = default;

void ContentTypeWidgetTest::shouldHaveDefaultValue()
{
    PimCommon::ContentTypeWidget widget;
    QVERIFY(widget.count() > 0);
    QCOMPARE(widget.currentIndex(), 0);
}

QTEST_MAIN(ContentTypeWidgetTest)

#include "moc_contenttypewidgettest.cpp"
