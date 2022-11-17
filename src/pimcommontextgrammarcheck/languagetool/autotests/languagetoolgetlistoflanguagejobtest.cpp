/*
   SPDX-FileCopyrightText: 2019-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "languagetoolgetlistoflanguagejobtest.h"
#include "languagetool/languagetoolgetlistoflanguagejob.h"
#include <QTest>
QTEST_GUILESS_MAIN(LanguageToolGetListOfLanguageJobTest)
LanguageToolGetListOfLanguageJobTest::LanguageToolGetListOfLanguageJobTest(QObject *parent)
    : QObject(parent)
{
}

void LanguageToolGetListOfLanguageJobTest::shouldHaveDefaultValues()
{
    PimCommonTextGrammarCheck::LanguageToolGetListOfLanguageJob w;
    QVERIFY(!w.canStart());
    QVERIFY(w.listOfLanguagePath().isEmpty());
    QVERIFY(w.url().isEmpty());
}

void LanguageToolGetListOfLanguageJobTest::shouldBeAbleToStart()
{
    PimCommonTextGrammarCheck::LanguageToolGetListOfLanguageJob job;
    QVERIFY(!job.canStart());
    job.setUrl(QStringLiteral("foo"));
    QVERIFY(!job.canStart());
    QNetworkAccessManager network;
    job.setNetworkAccessManager(&network);
    QVERIFY(job.canStart());
}
