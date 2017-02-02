/*
  Copyright (c) 2017 Montel Laurent <montel@kde.org>

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
#include "logactivitiesmanagertest.h"
#include "../logactivitiesmanager.h"

#include <QTest>

LogActivitiesManagerTest::LogActivitiesManagerTest(QObject *parent)
    : QObject(parent)
{

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

QTEST_MAIN(LogActivitiesManagerTest)
