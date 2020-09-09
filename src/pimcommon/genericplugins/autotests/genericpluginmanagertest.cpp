/*
  SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "genericpluginmanagertest.h"
#include "../genericpluginmanager.h"
#include <QTest>

GenericPluginManagerTest::GenericPluginManagerTest(QObject *parent)
    : QObject(parent)
{
}

GenericPluginManagerTest::~GenericPluginManagerTest()
{
}

void GenericPluginManagerTest::shouldHaveDefaultValue()
{
    PimCommon::GenericPluginManager pluginManager;
    QVERIFY(!pluginManager.initializePlugins());
}

void GenericPluginManagerTest::shouldInitialized()
{
    PimCommon::GenericPluginManager pluginManager;
    QVERIFY(!pluginManager.initializePlugins());
    pluginManager.setPluginDirectory(QStringLiteral("foo"));
    QVERIFY(!pluginManager.initializePlugins());
    pluginManager.setPluginName(QStringLiteral("foo"));
    QVERIFY(pluginManager.initializePlugins());
}

QTEST_MAIN(GenericPluginManagerTest)
