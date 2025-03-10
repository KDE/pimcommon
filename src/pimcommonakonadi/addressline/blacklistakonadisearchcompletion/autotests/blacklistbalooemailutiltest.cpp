/*
  SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "blacklistbalooemailutiltest.h"
#include "../blacklistakonadisearchemailutil.h"
#include <QTest>
BlackListBalooEmailUtilTest::BlackListBalooEmailUtilTest(QObject *parent)
    : QObject(parent)
{
}

BlackListBalooEmailUtilTest::~BlackListBalooEmailUtilTest() = default;

void BlackListBalooEmailUtilTest::shouldReturnEmptyResult()
{
    PimCommon::BlackListAkonadiSearchEmailUtil util;
    QVERIFY(util.createNewBlackList().isEmpty());
}

void BlackListBalooEmailUtilTest::shouldDontChangeWhenNotChanged()
{
    PimCommon::BlackListAkonadiSearchEmailUtil util;
    const QStringList lst = QStringList() << QStringLiteral("foo") << QStringLiteral("foo1") << QStringLiteral("foo2");
    util.initialBlackList(lst);
    QCOMPARE(util.createNewBlackList(), lst);
}

void BlackListBalooEmailUtilTest::shouldCreateNewList()
{
    PimCommon::BlackListAkonadiSearchEmailUtil util;
    const QStringList lst = QStringList() << QStringLiteral("foo") << QStringLiteral("foo1") << QStringLiteral("foo2");
    util.initialBlackList(lst);
    QHash<QString, bool> newList;
    newList.insert(QStringLiteral("foo"), false);
    util.setNewBlackList(newList);
    QCOMPARE(util.createNewBlackList(), QStringList() << QStringLiteral("foo1") << QStringLiteral("foo2"));
}

void BlackListBalooEmailUtilTest::shouldAddNewElements()
{
    PimCommon::BlackListAkonadiSearchEmailUtil util;
    QHash<QString, bool> newList;
    newList.insert(QStringLiteral("foo"), false);
    newList.insert(QStringLiteral("foo1"), false);
    newList.insert(QStringLiteral("foo2"), false);
    util.setNewBlackList(newList);
    QCOMPARE(util.createNewBlackList().count(), 0);

    newList.clear();
    newList.insert(QStringLiteral("foo"), true);
    newList.insert(QStringLiteral("foo1"), true);
    newList.insert(QStringLiteral("foo2"), true);
    util.setNewBlackList(newList);
    QCOMPARE(util.createNewBlackList().count(), 3);
}

QTEST_MAIN(BlackListBalooEmailUtilTest)

#include "moc_blacklistbalooemailutiltest.cpp"
