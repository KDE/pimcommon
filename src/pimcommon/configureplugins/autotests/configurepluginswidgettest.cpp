/*
  Copyright (c) 2016-2020 Laurent Montel <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License, version 2, as
  published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
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
