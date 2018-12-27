/*
  Copyright (C) 2017-2019 Montel Laurent <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License, version 2, as
  published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
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
    QCOMPARE(mainLayout->margin(), 0);

    KPIMTextEdit::PlainTextEditorWidget *mLog = w.findChild<KPIMTextEdit::PlainTextEditorWidget *>(QStringLiteral("log"));
    QVERIFY(mLog);
    QVERIFY(mLog->isReadOnly());
}

QTEST_MAIN(LogActivitiesWidgetTest)
