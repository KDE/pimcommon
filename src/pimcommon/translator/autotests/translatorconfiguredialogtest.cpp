/*
  SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "translatorconfiguredialogtest.h"
#include "translator/translatorconfiguredialog.h"
#include "translator/translatorconfigurewidget.h"
#include <QDialogButtonBox>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(TranslatorConfigureDialogTest)
TranslatorConfigureDialogTest::TranslatorConfigureDialogTest(QObject *parent)
    : QObject{parent}
{
}

void TranslatorConfigureDialogTest::shouldHaveDefaultValues()
{
    PimCommon::TranslatorConfigureDialog w;
    QVERIFY(!w.windowTitle().isEmpty());
    auto mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);

    auto mTranslatorConfigureWidget = w.findChild<PimCommon::TranslatorConfigureWidget *>(QStringLiteral("mTranslatorConfigureWidget"));
    QVERIFY(mTranslatorConfigureWidget);

    auto buttonBox = w.findChild<QDialogButtonBox *>(QStringLiteral("buttonBox"));
    QVERIFY(buttonBox);
}
