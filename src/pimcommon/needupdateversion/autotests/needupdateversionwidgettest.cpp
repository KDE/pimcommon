/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "needupdateversionwidgettest.h"
#include "needupdateversion/needupdateversionwidget.h"
#include <QTest>
QTEST_MAIN(NeedUpdateVersionWidgetTest)
NeedUpdateVersionWidgetTest::NeedUpdateVersionWidgetTest(QObject *parent)
    : QObject{parent}
{
}

NeedUpdateVersionWidgetTest::~NeedUpdateVersionWidgetTest() = default;

void NeedUpdateVersionWidgetTest::shouldHaveDefaultValues()
{
    PimCommon::NeedUpdateVersionWidget w;
    QVERIFY(w.isCloseButtonVisible());
}

#include "moc_needupdateversionwidgettest.cpp"
