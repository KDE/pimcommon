/*
  SPDX-FileCopyrightText: 2016-2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "configurepluginswidgettest.h"
#include "../configurepluginslistwidget.h"
#include "../configurepluginswidget.h"
#include <KMessageWidget>
#include <QSplitter>
#include <QStandardPaths>
#include <QTest>
#include <QTextEdit>

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

    auto mSplitter = w.findChild<QSplitter *>(QStringLiteral("splitter"));
    QVERIFY(mSplitter);
    QCOMPARE(mSplitter->count(), 2);

    auto mConfigureListWidget = mSplitter->findChild<PimCommon::ConfigurePluginsListWidget *>(QStringLiteral("configureListWidget"));
    QVERIFY(mConfigureListWidget);

    auto mDescription = mSplitter->findChild<QTextEdit *>(QStringLiteral("description"));
    QVERIFY(mDescription);
    QVERIFY(mDescription->isReadOnly());
    QVERIFY(mDescription->document()->isEmpty());
}

QTEST_MAIN(ConfigurePluginsWidgetTest)
