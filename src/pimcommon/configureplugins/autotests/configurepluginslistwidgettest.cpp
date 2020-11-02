/*
  SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "configurepluginslistwidgettest.h"
#include "../configurepluginslistwidget.h"
#include <QTest>
#include <QTreeWidget>
#include <QVBoxLayout>

ConfigurePluginsListWidgetTest::ConfigurePluginsListWidgetTest(QObject *parent)
    : QObject(parent)
{
}

ConfigurePluginsListWidgetTest::~ConfigurePluginsListWidgetTest()
{
}

void ConfigurePluginsListWidgetTest::shouldHaveDefaultValue()
{
    PimCommon::ConfigurePluginsListWidget w;

    auto *mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins(0, 0, 0, 0));

    auto *mListWidget = w.findChild<QTreeWidget *>(QStringLiteral("listwidget"));
    QVERIFY(mListWidget);
    QVERIFY(mListWidget->isSortingEnabled());
}

QTEST_MAIN(ConfigurePluginsListWidgetTest)
