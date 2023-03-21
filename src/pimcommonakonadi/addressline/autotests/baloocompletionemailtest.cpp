/*
  SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "baloocompletionemailtest.h"
#include "addressline/addresslineedit/baloocompletionemail.h"
#include <QTest>
BalooCompletionEmailTest::BalooCompletionEmailTest(QObject *parent)
    : QObject(parent)
{
}

BalooCompletionEmailTest::~BalooCompletionEmailTest() = default;

void BalooCompletionEmailTest::returnEmptyListWhenEmailListIsEmpty()
{
    PimCommon::BalooCompletionEmail completion;

    QVERIFY(completion.cleanupEmailList().isEmpty());
    PimCommon::BalooCompletionEmail::BalooCompletionEmailInfo info;
    QVERIFY(info.mListEmail.isEmpty());
    QVERIFY(info.mBlackList.isEmpty());
    QVERIFY(info.mExcludeEmailsRegularExpressions.isEmpty());
    QVERIFY(info.mListEmail.isEmpty());
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
    PimCommon::BalooCompletionEmail::BalooCompletionEmailInfo info;
    info.mListEmail = emailList;
    completion.setBalooCompletionEmailInfo(info);
    QCOMPARE(completion.cleanupEmailList(), emailList);
}

void BalooCompletionEmailTest::shouldReturnInterceptEmail()
{
    {
        PimCommon::BalooCompletionEmail completion;
        QStringList emailList;
        emailList << QStringLiteral("foo@kde.org");
        emailList << QStringLiteral("foo2@kde.org");
        emailList << QStringLiteral("foo3@bli.com");
        emailList << QStringLiteral("foo4@blo.com");
        emailList << QStringLiteral("foo5@bli.com");
        emailList << QStringLiteral("foo6@ff.com");
        PimCommon::BalooCompletionEmail::BalooCompletionEmailInfo info;
        info.mListEmail = emailList;
        QStringList excludeEmailsRegularExpressionsList;
        excludeEmailsRegularExpressionsList << QStringLiteral("foo6@ff\\.com");
        info.mExcludeEmailsRegularExpressions = excludeEmailsRegularExpressionsList;
        completion.setBalooCompletionEmailInfo(info);

        QStringList returnList;
        returnList << QStringLiteral("foo2@kde.org");
        returnList << QStringLiteral("foo3@bli.com");
        returnList << QStringLiteral("foo4@blo.com");
        returnList << QStringLiteral("foo5@bli.com");
        returnList << QStringLiteral("foo@kde.org");
        QCOMPARE(completion.cleanupEmailList(), returnList);
    }

    {
        PimCommon::BalooCompletionEmail completion;
        QStringList emailList;
        emailList << QStringLiteral("foo@kde.org");
        emailList << QStringLiteral("foo2@kde.org");
        emailList << QStringLiteral("foo3@bli.com");
        emailList << QStringLiteral("foo4@blo.com");
        emailList << QStringLiteral("foo5@bli.com");
        emailList << QStringLiteral("foo6@ff.com");
        PimCommon::BalooCompletionEmail::BalooCompletionEmailInfo info;
        info.mListEmail = emailList;
        QStringList excludeEmailsRegularExpressionsList;
        excludeEmailsRegularExpressionsList << QStringLiteral("foo.*@kde\\.org");
        info.mExcludeEmailsRegularExpressions = excludeEmailsRegularExpressionsList;
        completion.setBalooCompletionEmailInfo(info);

        QStringList returnList;
        returnList << QStringLiteral("foo3@bli.com");
        returnList << QStringLiteral("foo4@blo.com");
        returnList << QStringLiteral("foo5@bli.com");
        returnList << QStringLiteral("foo6@ff.com");
        QCOMPARE(completion.cleanupEmailList(), returnList);
    }
    {
        PimCommon::BalooCompletionEmail completion;
        QStringList emailList;
        emailList << QStringLiteral("foo@kde.org");
        emailList << QStringLiteral("foo2@kde.org");
        emailList << QStringLiteral("foo3@bli.com");
        emailList << QStringLiteral("foo4@blo.com");
        emailList << QStringLiteral("foo5@bli.com");
        emailList << QStringLiteral("foo6@ff.com");
        PimCommon::BalooCompletionEmail::BalooCompletionEmailInfo info;
        info.mListEmail = emailList;
        QStringList excludeEmailsRegularExpressionsList;
        excludeEmailsRegularExpressionsList << QStringLiteral("foo.*@kde\\.org");
        excludeEmailsRegularExpressionsList << QStringLiteral("foo6@ff\\.com");
        info.mExcludeEmailsRegularExpressions = excludeEmailsRegularExpressionsList;
        completion.setBalooCompletionEmailInfo(info);

        QStringList returnList;
        returnList << QStringLiteral("foo3@bli.com");
        returnList << QStringLiteral("foo4@blo.com");
        returnList << QStringLiteral("foo5@bli.com");
        QCOMPARE(completion.cleanupEmailList(), returnList);
    }
    {
        PimCommon::BalooCompletionEmail completion;
        QStringList emailList;
        emailList << QStringLiteral("foo@kde.org");
        emailList << QStringLiteral("foo2@kde.org");
        emailList << QStringLiteral("foo3@bli.com");
        emailList << QStringLiteral("foo4@blo.com");
        emailList << QStringLiteral("foo5@bli.com");
        emailList << QStringLiteral("foo6@ff.com");
        PimCommon::BalooCompletionEmail::BalooCompletionEmailInfo info;
        info.mListEmail = emailList;
        QStringList excludeEmailsRegularExpressionsList;
        excludeEmailsRegularExpressionsList << QStringLiteral("foo.*@kde\\.org");
        excludeEmailsRegularExpressionsList << QStringLiteral("foo6@ff\\.com");
        info.mExcludeEmailsRegularExpressions = excludeEmailsRegularExpressionsList;

        info.mExcludeDomains = QStringList() << QStringLiteral("bli.com");
        completion.setBalooCompletionEmailInfo(info);

        QStringList returnList;
        returnList << QStringLiteral("foo4@blo.com");
        QCOMPARE(completion.cleanupEmailList(), returnList);
    }
}

void BalooCompletionEmailTest::shouldReturnSameListIfBlackListInterceptEmail()
{
    PimCommon::BalooCompletionEmail completion;
    QStringList emailList;
    emailList << QStringLiteral("foo");
    emailList << QStringLiteral("foo2");
    emailList << QStringLiteral("foo3");
    emailList << QStringLiteral("foo4");
    emailList << QStringLiteral("foo5");
    emailList << QStringLiteral("foo6");
    PimCommon::BalooCompletionEmail::BalooCompletionEmailInfo info;
    info.mListEmail = emailList;
    completion.setBalooCompletionEmailInfo(info);

    QStringList blackList;
    blackList << QStringLiteral("foo");
    blackList << QStringLiteral("bla2");
    blackList << QStringLiteral("bla3");
    blackList << QStringLiteral("bla4");
    PimCommon::BalooCompletionEmail::BalooCompletionEmailInfo info2;
    info2.mListEmail = emailList;
    info2.mBlackList = blackList;
    completion.setBalooCompletionEmailInfo(info2);
    QStringList returnList;
    returnList << QStringLiteral("foo2");
    returnList << QStringLiteral("foo3");
    returnList << QStringLiteral("foo4");
    returnList << QStringLiteral("foo5");
    returnList << QStringLiteral("foo6");
    QCOMPARE(completion.cleanupEmailList(), returnList);
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
    PimCommon::BalooCompletionEmail::BalooCompletionEmailInfo info;
    info.mListEmail = emailList;
    completion.setBalooCompletionEmailInfo(info);

    QStringList blackList;
    blackList << QStringLiteral("bla");
    blackList << QStringLiteral("bla2");
    blackList << QStringLiteral("bla3");
    blackList << QStringLiteral("bla4");
    PimCommon::BalooCompletionEmail::BalooCompletionEmailInfo info2;
    info2.mListEmail = emailList;
    info2.mBlackList = blackList;
    completion.setBalooCompletionEmailInfo(info2);
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
    PimCommon::BalooCompletionEmail::BalooCompletionEmailInfo info;
    info.mListEmail = emailList;
    completion.setBalooCompletionEmailInfo(info);
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
    PimCommon::BalooCompletionEmail::BalooCompletionEmailInfo info;
    info.mListEmail = emailList;
    info.mBlackList = emailList;
    completion.setBalooCompletionEmailInfo(info);
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
    PimCommon::BalooCompletionEmail::BalooCompletionEmailInfo info;
    info.mListEmail = emailList;
    info.mExcludeDomains = QStringList() << QStringLiteral("kde.org");
    completion.setBalooCompletionEmailInfo(info);
    QVERIFY(completion.cleanupEmailList().isEmpty());

    const QString newAddress = QStringLiteral("foo6@linux.org");
    emailList << newAddress;
    info.mListEmail = emailList;
    completion.setBalooCompletionEmailInfo(info);
    QCOMPARE(completion.cleanupEmailList(), (QStringList() << newAddress));

    info.mExcludeDomains = QStringList() << QStringLiteral("kde.org") << QStringLiteral("linux.org");
    completion.setBalooCompletionEmailInfo(info);
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
    PimCommon::BalooCompletionEmail::BalooCompletionEmailInfo info;
    info.mListEmail = emailList;
    info.mExcludeDomains = QStringList() << QString();
    completion.setBalooCompletionEmailInfo(info);
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
    PimCommon::BalooCompletionEmail::BalooCompletionEmailInfo info;
    info.mListEmail = emailList;
    completion.setBalooCompletionEmailInfo(info);
    QCOMPARE(completion.cleanupEmailList(), emailList);
}

void BalooCompletionEmailTest::shouldExcludeDuplicateEntryWithDisplayName()
{
    PimCommon::BalooCompletionEmail completion;
    QStringList emailList;
    emailList << QStringLiteral("John Doe <doe@example.com>");
    emailList << QStringLiteral("\"John Doe\" <doe@example.com>");
    emailList << QStringLiteral("\"\'John Doe\'\" <doe@example.com>");

    PimCommon::BalooCompletionEmail::BalooCompletionEmailInfo info;
    info.mListEmail = emailList;
    completion.setBalooCompletionEmailInfo(info);
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
    PimCommon::BalooCompletionEmail::BalooCompletionEmailInfo info;
    info.mListEmail = emailList;
    completion.setBalooCompletionEmailInfo(info);
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
    PimCommon::BalooCompletionEmail::BalooCompletionEmailInfo info;
    info.mListEmail = emailList;
    completion.setBalooCompletionEmailInfo(info);
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
    PimCommon::BalooCompletionEmail::BalooCompletionEmailInfo info;
    info.mListEmail = emailList;
    completion.setBalooCompletionEmailInfo(info);
    QCOMPARE(completion.cleanupEmailList().count(), 1);
}

QTEST_MAIN(BalooCompletionEmailTest)
