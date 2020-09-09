/*
  SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

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
    QVBoxLayout *mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins(0, 0, 0, 0));

    KPIMTextEdit::PlainTextEditorWidget *mLog = w.findChild<KPIMTextEdit::PlainTextEditorWidget *>(QStringLiteral("log"));
    QVERIFY(mLog);
    QVERIFY(mLog->isReadOnly());
}

QTEST_MAIN(LogActivitiesWidgetTest)
