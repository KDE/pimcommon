/*
  SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "pluginutiltest.h"
#include <PimCommon/PluginUtil>
#include <QTest>

PluginUtilTest::PluginUtilTest(QObject *parent)
    : QObject(parent)
{
}

PluginUtilTest::~PluginUtilTest() = default;

void PluginUtilTest::shouldTestIsEnabled_data()
{
    QTest::addColumn<QStringList>("enabledPluginsList");
    QTest::addColumn<QStringList>("disabledPluginsList");
    QTest::addColumn<bool>("isEnabledByDefault");
    QTest::addColumn<QString>("pluginId");
    QTest::addColumn<bool>("result");

    // Use default value
    QTest::newRow("emptysettings") << QStringList() << QStringList() << true << QStringLiteral("foo") << true;
    QTest::newRow("emptysettings-2") << QStringList() << QStringList() << false << QStringLiteral("foo") << false;

    // Return false each time that pluginid is empty
    QTest::newRow("pluginidempty") << QStringList() << QStringList() << true << QString() << false;
    QTest::newRow("pluginidempty-2") << QStringList() << QStringList() << false << QString() << false;

    // Use setting from user settings
    QStringList disabled{QStringLiteral("foo")};
    QTest::newRow("usersettingdisabled") << QStringList() << disabled << true << QStringLiteral("foo") << false;
    QTest::newRow("usersettingdisabled-2") << QStringList() << disabled << false << QStringLiteral("foo") << false;

    QStringList enabled{QStringLiteral("foo")};
    QTest::newRow("usersettingenabled") << enabled << QStringList() << true << QStringLiteral("foo") << true;
    QTest::newRow("usersettingenabled-2") << enabled << QStringList() << false << QStringLiteral("foo") << true;
}

void PluginUtilTest::shouldTestIsEnabled()
{
    QFETCH(QStringList, enabledPluginsList);
    QFETCH(QStringList, disabledPluginsList);
    QFETCH(bool, isEnabledByDefault);
    QFETCH(QString, pluginId);
    QFETCH(bool, result);

    QCOMPARE(PimCommon::PluginUtil::isPluginActivated(enabledPluginsList, disabledPluginsList, isEnabledByDefault, pluginId), result);
}

QTEST_MAIN(PluginUtilTest)

#include "moc_pluginutiltest.cpp"
