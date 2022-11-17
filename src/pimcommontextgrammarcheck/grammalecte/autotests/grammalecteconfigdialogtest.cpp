/*
   SPDX-FileCopyrightText: 2019-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "grammalecteconfigdialogtest.h"
#include "grammalecte/grammalecteconfigdialog.h"
#include "grammalecte/grammalecteconfigwidget.h"
#include <QDialogButtonBox>
#include <QStandardPaths>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(GrammalecteConfigDialogTest)
GrammalecteConfigDialogTest::GrammalecteConfigDialogTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

void GrammalecteConfigDialogTest::shouldHaveDefaultValue()
{
    PimCommonTextGrammarCheck::GrammalecteConfigDialog w(nullptr, true);
    QVERIFY(!w.windowTitle().isEmpty());

    auto mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(mainLayout);

    auto mConfigWidget = w.findChild<PimCommonTextGrammarCheck::GrammalecteConfigWidget *>(QStringLiteral("configwidget"));
    QVERIFY(mConfigWidget);

    auto box = w.findChild<QDialogButtonBox *>(QStringLiteral("box"));
    QVERIFY(box);
}
