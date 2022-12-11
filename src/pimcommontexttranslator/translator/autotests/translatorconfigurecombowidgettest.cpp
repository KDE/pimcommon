/*
  SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "translatorconfigurecombowidgettest.h"
#include "translator/widgets/translatorconfigurecombowidget.h"
#include <QTest>
QTEST_MAIN(TranslatorConfigureComboWidgetTest)
TranslatorConfigureComboWidgetTest::TranslatorConfigureComboWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void TranslatorConfigureComboWidgetTest::shouldHaveDefaultValues()
{
    PimCommonTextTranslator::TranslatorConfigureComboWidget d;
    // TODO
}
