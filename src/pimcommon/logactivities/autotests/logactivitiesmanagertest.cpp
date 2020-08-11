/*
  SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/
#include "logactivitiesmanagertest.h"
#include "../logactivitiesmanager.h"

#include <QTest>
#include <QStandardPaths>

LogActivitiesManagerTest::LogActivitiesManagerTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

LogActivitiesManagerTest::~LogActivitiesManagerTest()
{
}

void LogActivitiesManagerTest::shouldHaveDefaultValue()
{
    PimCommon::LogActivitiesManager manager;
    QVERIFY(manager.log().isEmpty());
    QVERIFY(!manager.enableLogActivities());
}

void LogActivitiesManagerTest::shouldAppendLog()
{
    PimCommon::LogActivitiesManager manager;
    manager.setEnableLogActivities(false);
    manager.appendLog(QStringLiteral("ff"));
    QVERIFY(manager.log().isEmpty());

    manager.setEnableLogActivities(true);
    QVERIFY(manager.log().isEmpty());
    manager.appendLog(QStringLiteral("ff"));
    QVERIFY(!manager.log().isEmpty());
    manager.appendLog(QStringLiteral("ff"));
    QVERIFY(!manager.log().isEmpty());

    manager.clear();
    QVERIFY(manager.log().isEmpty());
}

void LogActivitiesManagerTest::shouldEnableActivities()
{
    PimCommon::LogActivitiesManager manager;
    QVERIFY(!manager.enableLogActivities());
    manager.setEnableLogActivities(true);
    QVERIFY(manager.enableLogActivities());
    manager.setEnableLogActivities(false);
    QVERIFY(!manager.enableLogActivities());
}

void LogActivitiesManagerTest::shouldClearLog()
{
    PimCommon::LogActivitiesManager manager;
    manager.setEnableLogActivities(true);
    manager.appendLog(QStringLiteral("ff"));
    QVERIFY(!manager.log().isEmpty());
    manager.setEnableLogActivities(false);
    QVERIFY(manager.log().isEmpty());
}

QTEST_MAIN(LogActivitiesManagerTest)
