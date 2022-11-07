/*
  SPDX-FileCopyrightText: 2014-2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "lineeditwithautocorrectiontest.h"
#include "../autocorrection.h"
#include <PimCommon/LineEditWithAutoCorrection>
#include <QTest>
#include <qtestkeyboard.h>

LineEditWithAutocorrectionTest::LineEditWithAutocorrectionTest() = default;

void LineEditWithAutocorrectionTest::shouldNotAutocorrectWhenDisabled()
{
    PimCommonAutoCorrection::LineEditWithAutoCorrection lineedit(nullptr, QStringLiteral("lineeditwithautocorrecttestrc"));
    QHash<QString, QString> entries;
    const QString originalWord = QStringLiteral("FOOFOO");
    const QString replaceWord = QStringLiteral("BLABLA");
    entries.insert(originalWord, replaceWord);
    auto settings = new PimCommonAutoCorrection::AutoCorrectionSettings;
    settings->setAutocorrectEntries(entries);
    lineedit.autocorrection()->setAutoCorrectionSettings(settings);
    lineedit.show();
    QVERIFY(QTest::qWaitForWindowExposed(&lineedit));
    QTest::keyClicks(&lineedit, originalWord);
    QTest::keyClick(&lineedit, ' ');
    QCOMPARE(lineedit.toPlainText(), QString(originalWord + QLatin1Char(' ')));
}

void LineEditWithAutocorrectionTest::shouldReplaceWordWhenExactText()
{
    PimCommonAutoCorrection::LineEditWithAutoCorrection lineedit(nullptr, QStringLiteral("lineeditwithautocorrecttestrc"));
    const QString originalWord = QStringLiteral("FOOFOO");
    const QString replaceWord = QStringLiteral("BLABLA");
    QHash<QString, QString> entries;
    entries.insert(originalWord, replaceWord);
    auto settings = new PimCommonAutoCorrection::AutoCorrectionSettings;
    settings->setAutocorrectEntries(entries);
    settings->setEnabledAutoCorrection(true);
    settings->setAdvancedAutocorrect(true);
    lineedit.autocorrection()->setAutoCorrectionSettings(settings);
    lineedit.show();
    QVERIFY(QTest::qWaitForWindowExposed(&lineedit));
    QTest::keyClicks(&lineedit, originalWord);
    QTest::keyClick(&lineedit, ' ');
    QCOMPARE(lineedit.toPlainText(), QString(replaceWord + QLatin1Char(' ')));
}

void LineEditWithAutocorrectionTest::shouldNotReplaceWordWhenInexactText()
{
    PimCommonAutoCorrection::LineEditWithAutoCorrection lineedit(nullptr, QStringLiteral("lineeditwithautocorrecttestrc"));
    const QString originalWord = QStringLiteral("FOOFOO");
    const QString replaceWord = QStringLiteral("BLABLA");
    QHash<QString, QString> entries;
    entries.insert(originalWord, replaceWord);
    auto settings = new PimCommonAutoCorrection::AutoCorrectionSettings;
    settings->setAutocorrectEntries(entries);
    settings->setEnabledAutoCorrection(true);
    settings->setAdvancedAutocorrect(true);
    lineedit.autocorrection()->setAutoCorrectionSettings(settings);
    lineedit.show();
    const QString nonExactText = QStringLiteral("BLIBLI");
    QVERIFY(QTest::qWaitForWindowExposed(&lineedit));
    QTest::keyClicks(&lineedit, nonExactText);
    QTest::keyClick(&lineedit, ' ');
    QCOMPARE(lineedit.toPlainText(), QString(nonExactText + QLatin1Char(' ')));
}

void LineEditWithAutocorrectionTest::shouldNotAddTwoSpace()
{
    PimCommonAutoCorrection::LineEditWithAutoCorrection lineedit(nullptr, QStringLiteral("lineeditwithautocorrecttestrc"));
    const QString originalWord = QStringLiteral("FOOFOO ");
    auto settings = new PimCommonAutoCorrection::AutoCorrectionSettings;
    settings->setSingleSpaces(true);
    settings->setEnabledAutoCorrection(true);
    lineedit.autocorrection()->setAutoCorrectionSettings(settings);
    lineedit.show();
    QVERIFY(QTest::qWaitForWindowExposed(&lineedit));
    QTest::keyClicks(&lineedit, originalWord);
    QTest::keyClick(&lineedit, ' ');
    QCOMPARE(lineedit.toPlainText(), originalWord);
}

QTEST_MAIN(LineEditWithAutocorrectionTest)
