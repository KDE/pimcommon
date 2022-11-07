/*
  SPDX-FileCopyrightText: 2014-2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "richtexteditwithautocorrectiontest.h"
#include "../autocorrection.h"
#include "../widgets/richtexteditwithautocorrection.h"
#include <QTest>
#include <qtestkeyboard.h>

RichTextEditWithAutoCorrectionTest::RichTextEditWithAutoCorrectionTest() = default;

void RichTextEditWithAutoCorrectionTest::shouldNotAutocorrectWhenDisabled()
{
    PimCommonAutoCorrection::RichTextEditWithAutoCorrection richtext(nullptr);
    QHash<QString, QString> entries;
    const QString originalWord = QStringLiteral("FOOFOO");
    const QString replaceWord = QStringLiteral("BLABLA");
    entries.insert(originalWord, replaceWord);
    auto settings = new PimCommonAutoCorrection::AutoCorrectionSettings;
    settings->setAutocorrectEntries(entries);
    richtext.autocorrection()->setAutoCorrectionSettings(settings);
    richtext.show();
    QVERIFY(QTest::qWaitForWindowExposed(&richtext));
    QTest::keyClicks(&richtext, originalWord);
    QTest::keyClick(&richtext, ' ');
    QCOMPARE(richtext.toPlainText(), QString(originalWord + QLatin1Char(' ')));
}

void RichTextEditWithAutoCorrectionTest::shouldReplaceWordWhenExactText()
{
    PimCommonAutoCorrection::RichTextEditWithAutoCorrection richtext(nullptr);
    const QString originalWord = QStringLiteral("FOOFOO");
    const QString replaceWord = QStringLiteral("BLABLA");
    QHash<QString, QString> entries;
    entries.insert(originalWord, replaceWord);
    auto settings = new PimCommonAutoCorrection::AutoCorrectionSettings;
    settings->setAutocorrectEntries(entries);
    settings->setEnabledAutoCorrection(true);
    settings->setAdvancedAutocorrect(true);
    richtext.autocorrection()->setAutoCorrectionSettings(settings);
    richtext.show();
    QVERIFY(QTest::qWaitForWindowExposed(&richtext));
    QTest::keyClicks(&richtext, originalWord);
    QTest::keyClick(&richtext, ' ');
    QCOMPARE(richtext.toPlainText(), QString(replaceWord + QLatin1Char(' ')));
}

void RichTextEditWithAutoCorrectionTest::shouldNotReplaceWordWhenInexactText()
{
    PimCommonAutoCorrection::RichTextEditWithAutoCorrection richtext(nullptr);
    const QString originalWord = QStringLiteral("FOOFOO");
    const QString replaceWord = QStringLiteral("BLABLA");
    QHash<QString, QString> entries;
    entries.insert(originalWord, replaceWord);
    auto settings = new PimCommonAutoCorrection::AutoCorrectionSettings;
    settings->setAutocorrectEntries(entries);
    settings->setEnabledAutoCorrection(true);
    settings->setAdvancedAutocorrect(true);
    richtext.autocorrection()->setAutoCorrectionSettings(settings);

    richtext.show();
    const QString nonExactText = QStringLiteral("BLIBLI");
    QVERIFY(QTest::qWaitForWindowExposed(&richtext));
    QTest::keyClicks(&richtext, nonExactText);
    QTest::keyClick(&richtext, ' ');
    QCOMPARE(richtext.toPlainText(), QString(nonExactText + QLatin1Char(' ')));
}

void RichTextEditWithAutoCorrectionTest::shouldReplaceWhenPressEnter()
{
    PimCommonAutoCorrection::RichTextEditWithAutoCorrection richtext(nullptr);
    const QString originalWord = QStringLiteral("FOOFOO");
    const QString replaceWord = QStringLiteral("BLABLA");
    QHash<QString, QString> entries;
    entries.insert(originalWord, replaceWord);

    auto settings = new PimCommonAutoCorrection::AutoCorrectionSettings;
    settings->setAutocorrectEntries(entries);
    settings->setEnabledAutoCorrection(true);
    settings->setAdvancedAutocorrect(true);
    richtext.autocorrection()->setAutoCorrectionSettings(settings);

    richtext.show();
    QVERIFY(QTest::qWaitForWindowExposed(&richtext));
    QTest::keyClicks(&richtext, originalWord);
    QTest::keyPress(&richtext, Qt::Key_Enter);
    QCOMPARE(richtext.toPlainText(), QString(replaceWord + QLatin1Char('\n')));
}

void RichTextEditWithAutoCorrectionTest::shouldReplaceWhenPressReturn()
{
    PimCommonAutoCorrection::RichTextEditWithAutoCorrection richtext(nullptr);
    const QString originalWord = QStringLiteral("FOOFOO");
    const QString replaceWord = QStringLiteral("BLABLA");
    QHash<QString, QString> entries;
    entries.insert(originalWord, replaceWord);
    auto settings = new PimCommonAutoCorrection::AutoCorrectionSettings;
    settings->setAutocorrectEntries(entries);
    settings->setEnabledAutoCorrection(true);
    settings->setAdvancedAutocorrect(true);
    richtext.autocorrection()->setAutoCorrectionSettings(settings);
    richtext.show();
    QVERIFY(QTest::qWaitForWindowExposed(&richtext));
    QTest::keyClicks(&richtext, originalWord);
    QTest::keyPress(&richtext, Qt::Key_Return);
    QCOMPARE(richtext.toPlainText(), QString(replaceWord + QLatin1Char('\n')));
}

QTEST_MAIN(RichTextEditWithAutoCorrectionTest)
