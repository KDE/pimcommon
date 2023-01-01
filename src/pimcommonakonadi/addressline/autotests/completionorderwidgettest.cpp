/*
  SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "completionorderwidgettest.h"
#include "../completionorder/completionorderwidget.h"
#include <QPushButton>
#include <QTest>
#include <QTreeWidget>

CompletionOrderWidgetTest::CompletionOrderWidgetTest(QObject *parent)
    : QObject(parent)
{
}

CompletionOrderWidgetTest::~CompletionOrderWidgetTest() = default;

void CompletionOrderWidgetTest::shouldHaveDefaultValue()
{
    PimCommon::CompletionOrderWidget w;
    auto treewidget = w.findChild<QTreeWidget *>(QStringLiteral("listview"));
    QVERIFY(treewidget);
    QVERIFY(treewidget->isHeaderHidden());
    QVERIFY(treewidget->isSortingEnabled());
    QCOMPARE(treewidget->topLevelItemCount(), 0);

    auto up = w.findChild<QPushButton *>(QStringLiteral("mUpButton"));
    QVERIFY(up);
    QVERIFY(up->autoRepeat());

    auto down = w.findChild<QPushButton *>(QStringLiteral("mDownButton"));
    QVERIFY(down);
    QVERIFY(down->autoRepeat());
}

QTEST_MAIN(CompletionOrderWidgetTest)
