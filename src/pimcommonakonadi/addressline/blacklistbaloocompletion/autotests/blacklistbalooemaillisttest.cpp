/*
  SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "blacklistbalooemaillisttest.h"
#include "../blacklistbalooemaillist.h"
#include <QTest>

BlackListBalooEmailListTest::BlackListBalooEmailListTest(QObject *parent)
    : QObject(parent)
{
}

BlackListBalooEmailListTest::~BlackListBalooEmailListTest()
{
}

void BlackListBalooEmailListTest::shouldHaveDefaultValue()
{
    PimCommon::BlackListBalooEmailList blackList;
    QVERIFY(blackList.count() == 0);
}

void BlackListBalooEmailListTest::shouldFillListEmail()
{
    PimCommon::BlackListBalooEmailList blackList;
    QCOMPARE(blackList.setEmailFound(QStringList() << QStringLiteral("foo@kde.org") << QStringLiteral("bla@kde.org") << QStringLiteral("bli@kde.org")), 3);
    QCOMPARE(blackList.count(), 3);
    for (int i = 0; i < blackList.count(); ++i) {
        QListWidgetItem *item = blackList.item(i);
        QVERIFY(item);
        auto *blackListItem = static_cast<PimCommon::BlackListBalooEmailListItem *>(item);
        QVERIFY(!blackListItem->initializeStatus());
        QCOMPARE(blackListItem->checkState(), Qt::Unchecked);
    }
    QVERIFY(blackList.blackListItemChanged().isEmpty());
}

void BlackListBalooEmailListTest::shouldFillListWithAlreadyBlackListedEmail()
{
    PimCommon::BlackListBalooEmailList blackList;
    const QStringList emails = QStringList() << QStringLiteral("foo@kde.org") << QStringLiteral("bla@kde.org") << QStringLiteral("bli@kde.org");
    blackList.setEmailBlackList(emails);
    QCOMPARE(blackList.setEmailFound(emails), 3);

    QCOMPARE(blackList.count(), 3);
    for (int i = 0; i < blackList.count(); ++i) {
        QListWidgetItem *item = blackList.item(i);
        QVERIFY(item);
        auto *blackListItem = static_cast<PimCommon::BlackListBalooEmailListItem *>(item);
        QVERIFY(blackListItem->initializeStatus());
        QCOMPARE(blackListItem->checkState(), Qt::Checked);
    }

    QVERIFY(blackList.blackListItemChanged().isEmpty());
}

void BlackListBalooEmailListTest::shouldReturnChangedItems()
{
    PimCommon::BlackListBalooEmailList blackList;
    const QStringList emails = QStringList() << QStringLiteral("foo@kde.org") << QStringLiteral("bla@kde.org") << QStringLiteral("bli@kde.org");
    blackList.setEmailBlackList(emails);
    QCOMPARE(blackList.setEmailFound(emails), 3);
    QListWidgetItem *item = blackList.item(1);
    QVERIFY(item);
    item->setCheckState(Qt::Unchecked);
    QVERIFY(!blackList.blackListItemChanged().isEmpty());
}

void BlackListBalooEmailListTest::shouldNotAddDuplicateEmails()
{
    PimCommon::BlackListBalooEmailList blackList;
    const QStringList emails = QStringList() << QStringLiteral("foo@kde.org") << QStringLiteral("bli@kde.org") << QStringLiteral("bli@kde.org");
    blackList.setEmailBlackList(emails);
    QCOMPARE(blackList.setEmailFound(emails), 2);

    QCOMPARE(blackList.count(), 2);
}

void BlackListBalooEmailListTest::shouldExcludeDomain()
{
    PimCommon::BlackListBalooEmailList blackList;
    blackList.setExcludeDomain(QStringList() << QStringLiteral("kde.org") << QStringLiteral("toto.fr"));
    QStringList emails = QStringList() << QStringLiteral("foo@kde.org") << QStringLiteral("bli@fr.fr") << QStringLiteral("bli@toto.fr");
    blackList.setEmailBlackList(emails);
    QCOMPARE(blackList.setEmailFound(emails), 1);

    QCOMPARE(blackList.count(), 1);

    blackList.setExcludeDomain(QStringList() << QStringLiteral("kde.org") << QStringLiteral("toto.fr"));
    emails = QStringList() << QStringLiteral("<foo@kde.org>") << QStringLiteral("bli@fr.fr") << QStringLiteral("bli@toto.fr");
    blackList.setEmailBlackList(emails);
    QCOMPARE(blackList.setEmailFound(emails), 1);
    QCOMPARE(blackList.count(), 1);
}

void BlackListBalooEmailListTest::shouldAvoidSameEmailWithDifferentCase()
{
    PimCommon::BlackListBalooEmailList blackList;
    const QStringList emails = QStringList() << QStringLiteral("foo@kde.org") << QStringLiteral("Foo@kde.org") << QStringLiteral("foo@kde.ORG");
    QCOMPARE(blackList.setEmailFound(emails), 1);

    QCOMPARE(blackList.count(), 1);
}

void BlackListBalooEmailListTest::shouldAvoidSameEmailWithDisplayNameOrNot()
{
    PimCommon::BlackListBalooEmailList blackList;
    const QStringList emails = QStringList() << QStringLiteral("foo@kde.org")
                                             << QStringLiteral("Bla Blo <Foo@kde.org>");
    QCOMPARE(blackList.setEmailFound(emails), 1);

    QCOMPARE(blackList.count(), 1);
}

QTEST_MAIN(BlackListBalooEmailListTest)
