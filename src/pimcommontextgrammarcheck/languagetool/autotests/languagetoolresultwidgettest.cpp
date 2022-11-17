/*
   SPDX-FileCopyrightText: 2019-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "languagetoolresultwidgettest.h"
#include "common/grammarresulttextedit.h"
#include "languagetool/languagetoolresultwidget.h"
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(LanguageToolResultWidgetTest)
LanguageToolResultWidgetTest::LanguageToolResultWidgetTest(QObject *parent)
    : QObject(parent)
{
}

void LanguageToolResultWidgetTest::shouldHaveDefaultValue()
{
    PimCommonTextGrammarCheck::LanguageToolResultWidget w;
    auto mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins());

    auto mResult = w.findChild<PimCommonTextGrammarCheck::GrammarResultTextEdit *>(QStringLiteral("grammarResult"));
    QVERIFY(mResult);
}
