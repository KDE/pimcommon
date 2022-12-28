/*
   SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "grammalecteurlrequesterwidgettest.h"
#include "grammalecte/grammalecteurlrequesterwidget.h"
#include <QHBoxLayout>
#include <QLineEdit>
#include <QTest>
#include <QToolButton>

QTEST_MAIN(GrammalecteUrlRequesterWidgetTest)

GrammalecteUrlRequesterWidgetTest::GrammalecteUrlRequesterWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void GrammalecteUrlRequesterWidgetTest::shouldHaveDefaultValues()
{
    PimCommonTextGrammarCheck::GrammalecteUrlRequesterWidget w;

    auto mainLayout = w.findChild<QHBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mLineEdit = w.findChild<QLineEdit *>(QStringLiteral("mLineEdit"));
    QVERIFY(mLineEdit);
    QVERIFY(mLineEdit->text().isEmpty());

    auto selectUrlButton = w.findChild<QToolButton *>(QStringLiteral("selectUrlButton"));
    QVERIFY(selectUrlButton);
    QVERIFY(!selectUrlButton->text().isEmpty());
}
