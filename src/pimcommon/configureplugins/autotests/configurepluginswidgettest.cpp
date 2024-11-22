/*
  SPDX-FileCopyrightText: 2016-2024 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "configurepluginswidgettest.h"
#include "../configurepluginslistwidget.h"
#include "../configurepluginswidget.h"
#include <KMessageWidget>
#include <QStandardPaths>
#include <QTest>

ConfigurePluginsWidgetTest::ConfigurePluginsWidgetTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

ConfigurePluginsWidgetTest::~ConfigurePluginsWidgetTest() = default;

void ConfigurePluginsWidgetTest::shouldHaveDefaultValue()
{
    PimCommon::ConfigurePluginsWidget w;

    auto mMessageWidget = w.findChild<KMessageWidget *>(QStringLiteral("mMessageWidget"));
    QVERIFY(mMessageWidget);
    QVERIFY(!mMessageWidget->isCloseButtonVisible());
    QVERIFY(!mMessageWidget->text().isEmpty());

    auto mConfigureListWidget = w.findChild<PimCommon::ConfigurePluginsListWidget *>(QStringLiteral("configureListWidget"));
    QVERIFY(mConfigureListWidget);
}

QTEST_MAIN(ConfigurePluginsWidgetTest)

#include "moc_configurepluginswidgettest.cpp"
