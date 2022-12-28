/*
   SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "grammalecteurlrequesterwidgettest.h"
#include "grammalecte/grammalecteurlrequesterwidget.h"
#include <QTest>

QTEST_MAIN(GrammalecteUrlRequesterWidgetTest)

GrammalecteUrlRequesterWidgetTest::GrammalecteUrlRequesterWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void GrammalecteUrlRequesterWidgetTest::shouldHaveDefaultValues()
{
    PimCommonTextGrammarCheck::GrammalecteUrlRequesterWidget w;
    // TODO
}
