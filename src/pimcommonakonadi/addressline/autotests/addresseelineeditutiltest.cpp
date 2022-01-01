/*
   SPDX-FileCopyrightText: 2016-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "addresseelineeditutiltest.h"
#include "../addresslineedit/addresseelineeditutil.h"
#include <QTest>

AddresseeLineEditUtilTest::AddresseeLineEditUtilTest(QObject *parent)
    : QObject(parent)
{
}

AddresseeLineEditUtilTest::~AddresseeLineEditUtilTest() = default;

void AddresseeLineEditUtilTest::shouldAdaptPasteMails_data()
{
    QTest::addColumn<QString>("input");
    QTest::addColumn<QString>("output");

    QTest::newRow("empty") << QString() << QString();
    QTest::newRow("onemail") << QStringLiteral("foo@kde.org") << QStringLiteral("foo@kde.org");
    QTest::newRow("onemailwithat") << QStringLiteral("foo (at) kde.org") << QStringLiteral("foo@kde.org");
    QTest::newRow("text") << QStringLiteral("fookde.org") << QStringLiteral("fookde.org");
    QTest::newRow("onemailwithdot") << QStringLiteral("foo at kde dot org") << QStringLiteral("foo@kde.org");
    QTest::newRow("mailto") << QStringLiteral("mailto:foo@kde.org") << QStringLiteral("foo@kde.org");
    QTest::newRow("multimail") << QStringLiteral("foo@kde.org,\r\n     bla@kde.org,blo@kde.org") << QStringLiteral("foo@kde.org,      bla@kde.org,blo@kde.org");
    QTest::newRow("multimail-2") << QStringLiteral("foo@kde.org,\r\n     bla@kde.org,blo@kde.org,   ")
                                 << QStringLiteral("foo@kde.org,      bla@kde.org,blo@kde.org");
    QTest::newRow("multimail-3") << QStringLiteral("foo@kde.org,\r\n     bla@kde.org,blo@kde.org,\n")
                                 << QStringLiteral("foo@kde.org,      bla@kde.org,blo@kde.org");
    QTest::newRow("multimail-4") << QStringLiteral("foo@kde.org,\r\n     bla@kde.org,blo@kde.org,    \n")
                                 << QStringLiteral("foo@kde.org,      bla@kde.org,blo@kde.org");
    QTest::newRow("multimail-5") << QStringLiteral("foo (at) kde.org,\r\n     bla (at) kde.org,blo (at) kde.org")
                                 << QStringLiteral("foo@kde.org,      bla@kde.org,blo@kde.org");
    QTest::newRow("multimail-6") << QStringLiteral("mailto:foo@kde.org,\r\n     bla@kde.org,blo@kde.org")
                                 << QStringLiteral("foo@kde.org,      bla@kde.org,blo@kde.org");
    QTest::newRow("multimail-7") << QStringLiteral("bla <foo@kde.org>,\r\n     bli <bla@kde.org>,blo <blo@kde.org>")
                                 << QStringLiteral("bla <foo@kde.org>,      bli <bla@kde.org>,blo <blo@kde.org>");
    QTest::newRow("multimail-8") << QStringLiteral("\"bla, v\" <foo@kde.org>,\r\n     \"bli, u\" <bla@kde.org>,\"blo, k\" <blo@kde.org>")
                                 << QStringLiteral("\"bla, v\" <foo@kde.org>,      \"bli, u\" <bla@kde.org>,\"blo, k\" <blo@kde.org>");
}

void AddresseeLineEditUtilTest::shouldAdaptPasteMails()
{
    QFETCH(QString, input);
    QFETCH(QString, output);
    QCOMPARE(PimCommon::AddresseeLineEditUtil::adaptPasteMails(input), output);
}

QTEST_MAIN(AddresseeLineEditUtilTest)
