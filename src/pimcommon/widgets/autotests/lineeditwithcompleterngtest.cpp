/*
  SPDX-FileCopyrightText: 2017-2024 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "lineeditwithcompleterngtest.h"
#include "../lineeditwithcompleterng.h"
#include <QCompleter>
#include <QTest>

QTEST_MAIN(LineEditWithCompleterNgTest)

LineEditWithCompleterNgTest::LineEditWithCompleterNgTest(QObject *parent)
    : QObject(parent)
{
}

void LineEditWithCompleterNgTest::shouldHaveDefaultValue()
{
    PimCommon::LineEditWithCompleterNg w;
    QVERIFY(w.completer());
    QVERIFY(w.completer()->model());
    QCOMPARE(w.completer()->model()->rowCount(), 0);
}

void LineEditWithCompleterNgTest::shouldAddCompletionItem()
{
    PimCommon::LineEditWithCompleterNg w;
    w.addCompletionItem(QStringLiteral("ff"));
    QCOMPARE(w.completer()->model()->rowCount(), 1);

    // Don't add same element
    w.addCompletionItem(QStringLiteral("ff"));
    QCOMPARE(w.completer()->model()->rowCount(), 1);

    w.addCompletionItem(QStringLiteral("ffss"));
    QCOMPARE(w.completer()->model()->rowCount(), 2);
}

void LineEditWithCompleterNgTest::shouldClearCompleter()
{
    PimCommon::LineEditWithCompleterNg w;
    for (int i = 0; i < 10; ++i) {
        w.addCompletionItem(QStringLiteral("ff%1").arg(i));
    }
    QCOMPARE(w.completer()->model()->rowCount(), 10);
    w.slotClearHistory();
    QCOMPARE(w.completer()->model()->rowCount(), 0);
}

#include "moc_lineeditwithcompleterngtest.cpp"
