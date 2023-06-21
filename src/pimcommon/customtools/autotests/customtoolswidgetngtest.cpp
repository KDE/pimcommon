/*
  SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "customtoolswidgetngtest.h"
#include "customtools/customtoolswidgetng.h"
#include <QStackedWidget>
#include <QStandardPaths>
#include <QTest>

CustomToolsWidgetNgTest::CustomToolsWidgetNgTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

CustomToolsWidgetNgTest::~CustomToolsWidgetNgTest() = default;

void CustomToolsWidgetNgTest::shouldHaveDefaultValue()
{
    PimCommon::CustomToolsWidgetNg widget;
    widget.show();

    auto stackWidget = widget.findChild<QStackedWidget *>(QStringLiteral("stackedwidget"));
    QVERIFY(stackWidget);
}

QTEST_MAIN(CustomToolsWidgetNgTest)

#include "moc_customtoolswidgetngtest.cpp"
