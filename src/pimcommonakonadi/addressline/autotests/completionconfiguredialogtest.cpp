/*
  SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "completionconfiguredialogtest.h"
#include "addressline/completionconfiguredialog/completionconfiguredialog.h"
#include <QDialogButtonBox>
#include <QStandardPaths>
#include <QTabWidget>
#include <QTest>

using namespace Qt::Literals::StringLiterals;

QTEST_MAIN(CompletionConfigureDialogTest)
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
    QCOMPARE(buttonBox->standardButtons(),
             QDialogButtonBox::StandardButtons{QDialogButtonBox::Ok | QDialogButtonBox::Apply | QDialogButtonBox::Cancel | QDialogButtonBox::RestoreDefaults});

    auto tabWidget = dlg.findChild<QTabWidget *>(QStringLiteral("tabwidget"));
    QVERIFY(tabWidget);
    QVERIFY(tabWidget->count() > 0);
    for (int i = 0; i < tabWidget->count(); ++i) {
        const QString objName = tabWidget->widget(i)->objectName();
        const bool hasName = (objName == "completionorder_widget"_L1) || (objName == "recentaddress_widget"_L1) || (objName == "blacklistbaloo_widget"_L1);
        QVERIFY(hasName);
    }
}

#include "moc_completionconfiguredialogtest.cpp"
