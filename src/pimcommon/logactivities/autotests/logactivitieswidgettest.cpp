/*
  SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "logactivitieswidgettest.h"
#include "../logactivitieswidget.h"
#include <KPIMTextEdit/PlainTextEditorWidget>
#include <QTest>
#include <QVBoxLayout>

LogActivitiesWidgetTest::LogActivitiesWidgetTest(QObject *parent)
    : QObject(parent)
{
}

LogActivitiesWidgetTest::~LogActivitiesWidgetTest()
{
}

void LogActivitiesWidgetTest::shouldHaveDefaultValue()
{
    PimCommon::LogActivitiesWidget w;
    auto mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins(0, 0, 0, 0));

    auto mLog = w.findChild<KPIMTextEdit::PlainTextEditorWidget *>(QStringLiteral("log"));
    QVERIFY(mLog);
    QVERIFY(mLog->isReadOnly());
}

QTEST_MAIN(LogActivitiesWidgetTest)
