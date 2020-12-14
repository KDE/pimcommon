/*
  SPDX-FileCopyrightText: 2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "importkmailautocorrectiontest.h"
#include "autocorrection/import/importkmailautocorrection.h"
#include <QTest>
QTEST_MAIN(ImportKMailAutocorrectionTest)

ImportKMailAutocorrectionTest::ImportKMailAutocorrectionTest(QObject *parent)
    : QObject(parent)
{

}

void ImportKMailAutocorrectionTest::shouldHaveDefaultValues()
{
    PimCommon::ImportKMailAutocorrection import;
    QVERIFY(import.upperCaseExceptions().isEmpty());
    QVERIFY(import.twoUpperLetterExceptions().isEmpty());
    QVERIFY(import.autocorrectEntries().isEmpty());
    QVERIFY(import.superScriptEntries().isEmpty());

    QCOMPARE(import.typographicSingleQuotes().begin, QChar());
    QCOMPARE(import.typographicSingleQuotes().end, QChar());
    QCOMPARE(import.typographicDoubleQuotes().begin, QChar());
    QCOMPARE(import.typographicDoubleQuotes().end, QChar());

    QCOMPARE(import.maxFindStringLenght(), 0);
    QCOMPARE(import.minFindStringLenght(), 0);
}

void ImportKMailAutocorrectionTest::shouldLoadFile()
{
    const QString originalFile = QLatin1String(AUTOCORRECTION_DATA_DIR) + QStringLiteral("/custom-fr.xml");
    PimCommon::ImportKMailAutocorrection import;
    QVERIFY(import.import(originalFile));
    QCOMPARE(import.typographicSingleQuotes().begin, QStringLiteral("‘"));
    QCOMPARE(import.typographicSingleQuotes().end, QStringLiteral("’"));
    QCOMPARE(import.typographicDoubleQuotes().begin, QStringLiteral("“"));
    QCOMPARE(import.typographicDoubleQuotes().end, QStringLiteral("”"));
}