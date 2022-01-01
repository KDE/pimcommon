/*
  SPDX-FileCopyrightText: 2015-2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "completionconfiguredialogtest.h"
#include "../completionconfiguredialog/completionconfiguredialog.h"
#include <QDialogButtonBox>
#include <QStandardPaths>
#include <QTabWidget>
#include <QTest>

CompletionConfigureDialogTest::CompletionConfigureDialogTest(QObject *parent)
    : QObject(parent)
{
}

CompletionConfigureDialogTest::~CompletionConfigureDialogTest() = default;

void CompletionConfigureDialogTest::initTestCase()
{
    QStandardPaths::setTestModeEnabled(true);
}

void CompletionConfigureDialogTest::shouldHaveDefaultValue()
{
    PimCommon::CompletionConfigureDialog dlg;

    auto buttonBox = dlg.findChild<QDialogButtonBox *>(QStringLiteral("buttonbox"));
    QVERIFY(buttonBox);

    auto tabWidget = dlg.findChild<QTabWidget *>(QStringLiteral("tabwidget"));
    QVERIFY(tabWidget);
    QVERIFY(tabWidget->count() > 0);
    for (int i = 0; i < tabWidget->count(); ++i) {
        const QString objName = tabWidget->widget(i)->objectName();
        const bool hasName = (objName == QLatin1String("completionorder_widget")) || (objName == QLatin1String("recentaddress_widget"))
            || (objName == QLatin1String("blacklistbaloo_widget"));
        QVERIFY(hasName);
    }
}

QTEST_MAIN(CompletionConfigureDialogTest)
