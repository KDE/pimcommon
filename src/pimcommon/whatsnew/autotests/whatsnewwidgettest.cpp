/*
   SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "whatsnewwidgettest.h"
#include "whatsnew/whatsnewcomboboxwidget.h"
#include "whatsnew/whatsnewwidget.h"
#include <QTest>
#include <QTextBrowser>
#include <QVBoxLayout>

QTEST_MAIN(WhatsNewWidgetTest)
WhatsNewWidgetTest::WhatsNewWidgetTest(QWidget *parent)
    : QWidget{parent}
{
}

void WhatsNewWidgetTest::shouldHaveDefaultValues()
{
    PimCommon::WhatsNewWidget w({});
    auto mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mLabelInfo = w.findChild<QTextBrowser *>(QStringLiteral("mLabelInfo"));
    QVERIFY(mLabelInfo);
    QVERIFY(mLabelInfo->toPlainText().isEmpty());
    QVERIFY(mLabelInfo->openExternalLinks());

    auto mWhatsNewComboBoxWidget = w.findChild<PimCommon::WhatsNewComboBoxWidget *>(QStringLiteral("mWhatsNewComboBoxWidget"));
    QVERIFY(mWhatsNewComboBoxWidget);
}

#include "moc_whatsnewwidgettest.cpp"
