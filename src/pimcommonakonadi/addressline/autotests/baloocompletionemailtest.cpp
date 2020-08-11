/*
  SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "baloocompletionemailtest.h"
#include <QTest>
#include "../addresslineedit/baloocompletionemail.h"
BalooCompletionEmailTest::BalooCompletionEmailTest(QObject *parent)
    : QObject(parent)
{
}

BalooCompletionEmailTest::~BalooCompletionEmailTest()
{
}

void BalooCompletionEmailTest::returnEmptyListWhenEmailListIsEmpty()
{
    PimCommon::BalooCompletionEmail completion;
    QVERIFY(completion.cleanupEmailList().isEmpty());
}

void BalooCompletionEmailTest::shouldReturnSameListWhenNotExclude()
{
    PimCommon::BalooCompletionEmail completion;
    QStringList emailList;
    emailList << QStringLiteral("foo");
    emailList << QStringLiteral("foo2");
    emailList << QStringLiteral("foo3");
    emailList << QStringLiteral("foo4");
    emailList << QStringLiteral("foo5");
    emailList << QStringLiteral("foo6");
    completion.setEmailList(emailList);
    QCOMPARE(completion.cleanupEmailList(), emailList);
}

void BalooCompletionEmailTest::shouldReturnSameListIfBlackListDoesntInterceptEmail()
{
    PimCommon::BalooCompletionEmail completion;
    QStringList emailList;
    emailList << QStringLiteral("foo");
    emailList << QStringLiteral("foo2");
    emailList << QStringLiteral("foo3");
    emailList << QStringLiteral("foo4");
    emailList << QStringLiteral("foo5");
    emailList << QStringLiteral("foo6");
    completion.setEmailList(emailList);

    QStringList blackList;
    blackList << QStringLiteral("bla");
    blackList << QStringLiteral("bla2");
    blackList << QStringLiteral("bla3");
    blackList << QStringLiteral("bla4");
    completion.setBlackList(blackList);
    QCOMPARE(completion.cleanupEmailList(), emailList);
}

void BalooCompletionEmailTest::shouldReturnUniqueEmail()
{
    PimCommon::BalooCompletionEmail completion;
    QStringList emailList;
    emailList << QStringLiteral("foo");
    emailList << QStringLiteral("foo");
    emailList << QStringLiteral("foo1");
    emailList << QStringLiteral("foo");
    emailList << QStringLiteral("foo1");
    emailList << QStringLiteral("foo2");
    completion.setEmailList(emailList);
    QCOMPARE(completion.cleanupEmailList(), (QStringList() << QStringLiteral("foo") << QStringLiteral("foo1") << QStringLiteral("foo2")));
}

void BalooCompletionEmailTest::shouldReturnEmptyListWhenAllBlackListed()
{
    PimCommon::BalooCompletionEmail completion;
    QStringList emailList;
    emailList << QStringLiteral("foo");
    emailList << QStringLiteral("foo2");
    emailList << QStringLiteral("foo3");
    emailList << QStringLiteral("foo4");
    emailList << QStringLiteral("foo5");
    emailList << QStringLiteral("foo6");
    completion.setEmailList(emailList);
    completion.setBlackList(emailList);
    QVERIFY(completion.cleanupEmailList().isEmpty());
}

void BalooCompletionEmailTest::shouldExcludeDomain()
{
    PimCommon::BalooCompletionEmail completion;
    QStringList emailList;
    emailList << QStringLiteral("foo@kde.org");
    emailList << QStringLiteral("foo2@kde.org");
    emailList << QStringLiteral("foo3@kde.org");
    emailList << QStringLiteral("foo4@kde.org");
    emailList << QStringLiteral("foo5@kde.org");
    emailList << QStringLiteral("foo6@kde.org");
    completion.setEmailList(emailList);
    completion.setExcludeDomain(QStringList() << QStringLiteral("kde.org"));
    QVERIFY(completion.cleanupEmailList().isEmpty());

    const QString newAddress = QStringLiteral("foo6@linux.org");
    emailList << newAddress;
    completion.setEmailList(emailList);
    QCOMPARE(completion.cleanupEmailList(), (QStringList() << newAddress));

    completion.setExcludeDomain(QStringList() << QStringLiteral("kde.org") << QStringLiteral("linux.org"));
    QVERIFY(completion.cleanupEmailList().isEmpty());
}

void BalooCompletionEmailTest::shouldReturnEmailListWhenDomainListIsNotNull()
{
    PimCommon::BalooCompletionEmail completion;
    QStringList emailList;
    emailList << QStringLiteral("foo@kde.org");
    emailList << QStringLiteral("foo2@kde.org");
    emailList << QStringLiteral("foo3@kde.org");
    emailList << QStringLiteral("foo4@kde.org");
    emailList << QStringLiteral("foo5@kde.org");
    emailList << QStringLiteral("foo6@kde.org");
    emailList.sort();
    completion.setEmailList(emailList);
    completion.setExcludeDomain(QStringList() << QString());
    QCOMPARE(completion.cleanupEmailList(), emailList);
}

void BalooCompletionEmailTest::shouldDontDuplicateEmailWhenUseCase()
{
    PimCommon::BalooCompletionEmail completion;
    QStringList emailList;
    emailList << QStringLiteral("foo");
    emailList << QStringLiteral("foo2");
    emailList << QStringLiteral("foo3");
    emailList << QStringLiteral("foo4");
    emailList << QStringLiteral("foo5");
    emailList << QStringLiteral("foo6");

    QStringList caseEmailList;
    caseEmailList << QStringLiteral("Foo");
    caseEmailList << QStringLiteral("fOo2");
    caseEmailList << QStringLiteral("FOo3");
    completion.setEmailList((QStringList() << emailList << caseEmailList));
    QCOMPARE(completion.cleanupEmailList(), emailList);
}

void BalooCompletionEmailTest::shouldExcludeDuplicateEntryWithDisplayName()
{
    PimCommon::BalooCompletionEmail completion;
    QStringList emailList;
    emailList << QStringLiteral("John Doe <doe@example.com>");
    emailList << QStringLiteral("\"John Doe\" <doe@example.com>");
    emailList << QStringLiteral("\"\'John Doe\'\" <doe@example.com>");
    completion.setEmailList(emailList);
    QCOMPARE(completion.cleanupEmailList().count(), 1);
}

void BalooCompletionEmailTest::shouldExcludeDuplicateEntryWithDisplayNameAddAddressWithDifferentCase()
{
    PimCommon::BalooCompletionEmail completion;
    QStringList emailList;
    emailList << QStringLiteral("John Doe <doe@example.com>");
    emailList << QStringLiteral("\"John Doe\" <doe@example.com>");
    emailList << QStringLiteral("\"\'John Doe\'\" <doe@example.com>");
    emailList << QStringLiteral("\"\"\"\"\'John Doe\'\"\"\"\" <doe@example.com>");
    emailList << QStringLiteral("John Doe <Doe@example.com>");
    emailList << QStringLiteral("John Doe <DOE@example.com>");
    emailList << QStringLiteral("John Doe <dOE@example.com>");
    completion.setEmailList(emailList);
    QCOMPARE(completion.cleanupEmailList().count(), 1);
}

void BalooCompletionEmailTest::shouldExcludeDuplicateEntryWithDifferentDisplayNameAddAddressWithDifferentCase()
{
    PimCommon::BalooCompletionEmail completion;
    QStringList emailList;
    emailList << QStringLiteral("John Doe <doe@example.com>");
    emailList << QStringLiteral("\"John Doe\" <doe@example.com>");
    emailList << QStringLiteral("\"\'John Doe\'\" <doe@example.com>");
    emailList << QStringLiteral("John Doe <doe@example.com>");
    emailList << QStringLiteral("Doe John <Doe@example.com>");
    emailList << QStringLiteral("John <DOE@example.com>");
    emailList << QStringLiteral("Doe <dOE@example.com>");
    completion.setEmailList(emailList);
    QCOMPARE(completion.cleanupEmailList().count(), 1);
}

void BalooCompletionEmailTest::shouldExcludeEmptyNameWithDisplayNameForSameAddress()
{
    PimCommon::BalooCompletionEmail completion;
    QStringList emailList;
    emailList << QStringLiteral("doe@example.com");
    emailList << QStringLiteral("Doe John <Doe@example.com>");
    emailList << QStringLiteral("John <DOE@example.com>");
    emailList << QStringLiteral("Doe <dOE@example.com>");
    completion.setEmailList(emailList);
    QCOMPARE(completion.cleanupEmailList().count(), 1);
}

QTEST_MAIN(BalooCompletionEmailTest)
