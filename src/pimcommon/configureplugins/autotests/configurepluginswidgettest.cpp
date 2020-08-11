/*
  SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#include "configurepluginswidgettest.h"
#include "../configurepluginswidget.h"
#include "../configurepluginslistwidget.h"
#include <QTextEdit>
#include <KMessageWidget>
#include <QSplitter>
#include <QTest>
#include <QStandardPaths>

ConfigurePluginsWidgetTest::ConfigurePluginsWidgetTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

ConfigurePluginsWidgetTest::~ConfigurePluginsWidgetTest()
{
}

void ConfigurePluginsWidgetTest::shouldHaveDefaultValue()
{
    PimCommon::ConfigurePluginsWidget w;

    KMessageWidget *mMessageWidget = w.findChild<KMessageWidget *>(QStringLiteral("mMessageWidget"));
    QVERIFY(mMessageWidget);
    QVERIFY(!mMessageWidget->isCloseButtonVisible());
    QVERIFY(!mMessageWidget->text().isEmpty());

    QSplitter *mSplitter = w.findChild<QSplitter *>(QStringLiteral("splitter"));
    QVERIFY(mSplitter);
    QCOMPARE(mSplitter->count(), 2);

    PimCommon::ConfigurePluginsListWidget *mConfigureListWidget = mSplitter->findChild<PimCommon::ConfigurePluginsListWidget *>(QStringLiteral("configureListWidget"));
    QVERIFY(mConfigureListWidget);

    QTextEdit *mDescription = mSplitter->findChild<QTextEdit *>(QStringLiteral("description"));
    QVERIFY(mDescription);
    QVERIFY(mDescription->isReadOnly());
    QVERIFY(mDescription->document()->isEmpty());
}

QTEST_MAIN(ConfigurePluginsWidgetTest)
