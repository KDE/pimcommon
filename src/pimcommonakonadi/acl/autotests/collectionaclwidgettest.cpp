/*
  SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "collectionaclwidgettest.h"
#include "../collectionaclwidget.h"
#include <QListView>
#include <QPushButton>
#include <QTest>

CollectionAclWidgetTest::CollectionAclWidgetTest(QObject *parent)
    : QObject(parent)
{
}

CollectionAclWidgetTest::~CollectionAclWidgetTest()
{
}

void CollectionAclWidgetTest::shouldHaveDefaultValue()
{
    PimCommon::CollectionAclWidget w;
    QVERIFY(w.aclManager());
    QListView *listView = w.findChild<QListView *>(QStringLiteral("list_view"));
    QVERIFY(listView);
    QPushButton *button = w.findChild<QPushButton *>(QStringLiteral("add"));
    QVERIFY(button);
    button = w.findChild<QPushButton *>(QStringLiteral("edit"));
    QVERIFY(button);
    button = w.findChild<QPushButton *>(QStringLiteral("delete"));
    QVERIFY(button);
}

QTEST_MAIN(CollectionAclWidgetTest)
