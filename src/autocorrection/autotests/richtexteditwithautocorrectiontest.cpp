/*
  Copyright (c) 2014-2017 Montel Laurent <montel@kde.org>

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

#include "richtexteditwithautocorrectiontest.h"
#include <qtest.h>
#include "../widgets/richtexteditwithautocorrection.h"
#include "../autocorrection.h"
#include <qtestkeyboard.h>

RichTextEditWithAutoCorrectionTest::RichTextEditWithAutoCorrectionTest()
{
}

void RichTextEditWithAutoCorrectionTest::shouldNotAutocorrectWhenDisabled()
{
    PimCommon::RichTextEditWithAutoCorrection richtext(nullptr);
    QHash<QString, QString> entries;
    const QString originalWord = QStringLiteral("FOOFOO");
    const QString replaceWord = QStringLiteral("BLABLA");
    entries.insert(originalWord, replaceWord);
    richtext.autocorrection()->setAutocorrectEntries(entries);
    richtext.show();
    QTest::qWaitForWindowExposed(&richtext);
    QTest::keyClicks(&richtext, originalWord);
    QTest::keyClick(&richtext, ' ');
    QCOMPARE(richtext.toPlainText(), QString(originalWord + QLatin1Char(' ')));
}

void RichTextEditWithAutoCorrectionTest::shouldReplaceWordWhenExactText()
{
    PimCommon::RichTextEditWithAutoCorrection richtext(nullptr);
    const QString originalWord = QStringLiteral("FOOFOO");
    const QString replaceWord = QStringLiteral("BLABLA");
    QHash<QString, QString> entries;
    entries.insert(originalWord, replaceWord);
    richtext.autocorrection()->setAutocorrectEntries(entries);
    richtext.autocorrection()->setEnabledAutoCorrection(true);
    richtext.autocorrection()->setAdvancedAutocorrect(true);
    richtext.show();
    QTest::qWaitForWindowExposed(&richtext);
    QTest::keyClicks(&richtext, originalWord);
    QTest::keyClick(&richtext, ' ');
    QCOMPARE(richtext.toPlainText(), QString(replaceWord + QLatin1Char(' ')));
}

void RichTextEditWithAutoCorrectionTest::shouldNotReplaceWordWhenInexactText()
{
    PimCommon::RichTextEditWithAutoCorrection richtext(nullptr);
    const QString originalWord = QStringLiteral("FOOFOO");
    const QString replaceWord = QStringLiteral("BLABLA");
    QHash<QString, QString> entries;
    entries.insert(originalWord, replaceWord);
    richtext.autocorrection()->setAutocorrectEntries(entries);
    richtext.autocorrection()->setEnabledAutoCorrection(true);
    richtext.autocorrection()->setAdvancedAutocorrect(true);
    richtext.show();
    const QString nonExactText = QStringLiteral("BLIBLI");
    QTest::qWaitForWindowExposed(&richtext);
    QTest::keyClicks(&richtext, nonExactText);
    QTest::keyClick(&richtext, ' ');
    QCOMPARE(richtext.toPlainText(), QString(nonExactText + QLatin1Char(' ')));
}

void RichTextEditWithAutoCorrectionTest::shouldReplaceWhenPressEnter()
{
    PimCommon::RichTextEditWithAutoCorrection richtext(nullptr);
    const QString originalWord = QStringLiteral("FOOFOO");
    const QString replaceWord = QStringLiteral("BLABLA");
    QHash<QString, QString> entries;
    entries.insert(originalWord, replaceWord);
    richtext.autocorrection()->setAutocorrectEntries(entries);
    richtext.autocorrection()->setEnabledAutoCorrection(true);
    richtext.autocorrection()->setAdvancedAutocorrect(true);
    richtext.show();
    QTest::qWaitForWindowExposed(&richtext);
    QTest::keyClicks(&richtext, originalWord);
    QTest::keyPress(&richtext, Qt::Key_Enter);
    QCOMPARE(richtext.toPlainText(), QString(replaceWord + QLatin1Char('\n')));
}

void RichTextEditWithAutoCorrectionTest::shouldReplaceWhenPressReturn()
{
    PimCommon::RichTextEditWithAutoCorrection richtext(nullptr);
    const QString originalWord = QStringLiteral("FOOFOO");
    const QString replaceWord = QStringLiteral("BLABLA");
    QHash<QString, QString> entries;
    entries.insert(originalWord, replaceWord);
    richtext.autocorrection()->setAutocorrectEntries(entries);
    richtext.autocorrection()->setEnabledAutoCorrection(true);
    richtext.autocorrection()->setAdvancedAutocorrect(true);
    richtext.show();
    QTest::qWaitForWindowExposed(&richtext);
    QTest::keyClicks(&richtext, originalWord);
    QTest::keyPress(&richtext, Qt::Key_Return);
    QCOMPARE(richtext.toPlainText(), QString(replaceWord + QLatin1Char('\n')));
}

QTEST_MAIN(RichTextEditWithAutoCorrectionTest)
