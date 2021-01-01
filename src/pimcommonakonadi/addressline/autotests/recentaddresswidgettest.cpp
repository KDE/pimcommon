/*
  SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "recentaddresswidgettest.h"
#include "../recentaddress/recentaddresswidget.h"
#include <QLineEdit>
#include <QToolButton>
#include <QListWidget>
#include <QTest>
#include <qtestmouse.h>

RecentAddressWidgetTest::RecentAddressWidgetTest(QObject *parent)
    : QObject(parent)
{
}

RecentAddressWidgetTest::~RecentAddressWidgetTest()
{
}

void RecentAddressWidgetTest::shouldHaveDefaultValue()
{
    PimCommon::RecentAddressWidget w;
    auto *lineedit = w.findChild<QLineEdit *>(QStringLiteral("line_edit"));
    QVERIFY(lineedit);
    QVERIFY(lineedit->isClearButtonEnabled());
    QVERIFY(lineedit->text().isEmpty());

    auto *newButton = w.findChild<QToolButton *>(QStringLiteral("new_button"));
    QVERIFY(newButton);

    auto *removeButton = w.findChild<QToolButton *>(QStringLiteral("remove_button"));
    QVERIFY(removeButton);
    QVERIFY(!removeButton->isEnabled());

    auto *listview = w.findChild<QListWidget *>(QStringLiteral("list_view"));
    QVERIFY(listview);
    QCOMPARE(listview->count(), 0);
}

void RecentAddressWidgetTest::shouldAddAddresses()
{
    PimCommon::RecentAddressWidget w;
    auto *listview = w.findChild<QListWidget *>(QStringLiteral("list_view"));
    QCOMPARE(listview->count(), 0);
    QStringList lst;
    lst << QStringLiteral("foo");
    lst << QStringLiteral("foo1");
    lst << QStringLiteral("foo2");
    w.setAddresses(lst);
    QCOMPARE(listview->count(), lst.count());
    //Clear list before to add
    w.setAddresses(lst);
    QCOMPARE(listview->count(), lst.count());
}

void RecentAddressWidgetTest::shouldInformThatItWasChanged()
{
    PimCommon::RecentAddressWidget w;
    QVERIFY(!w.wasChanged());
    auto *lineedit = w.findChild<QLineEdit *>(QStringLiteral("line_edit"));
    lineedit->setText(QStringLiteral("foo"));
    auto *newButton = w.findChild<QToolButton *>(QStringLiteral("new_button"));
    QVERIFY(newButton);
    QVERIFY(newButton->isEnabled());
    QTest::mouseClick(newButton, Qt::LeftButton);
    QVERIFY(w.wasChanged());
    auto *listview = w.findChild<QListWidget *>(QStringLiteral("list_view"));
    QCOMPARE(listview->count(), 1);
}

void RecentAddressWidgetTest::shouldNotAddMultiSameLine()
{
    PimCommon::RecentAddressWidget w;
    auto *lineedit = w.findChild<QLineEdit *>(QStringLiteral("line_edit"));
    auto *newButton = w.findChild<QToolButton *>(QStringLiteral("new_button"));

    auto *listview = w.findChild<QListWidget *>(QStringLiteral("list_view"));
    QCOMPARE(listview->count(), 0);

    lineedit->setText(QStringLiteral("foo"));
    QVERIFY(newButton->isEnabled());
    QTest::mouseClick(newButton, Qt::LeftButton);
    QCOMPARE(listview->count(), 1);

    QTest::mouseClick(newButton, Qt::LeftButton);
    QCOMPARE(listview->count(), 1);
}

void RecentAddressWidgetTest::shouldNotAddEmptyLine()
{
    PimCommon::RecentAddressWidget w;
    auto *lineedit = w.findChild<QLineEdit *>(QStringLiteral("line_edit"));
    auto *newButton = w.findChild<QToolButton *>(QStringLiteral("new_button"));
    auto *listview = w.findChild<QListWidget *>(QStringLiteral("list_view"));
    QCOMPARE(listview->count(), 0);
    QVERIFY(lineedit->text().isEmpty());
    QVERIFY(!newButton->isEnabled());

    QTest::mouseClick(newButton, Qt::LeftButton);
    QCOMPARE(listview->count(), 0);

    QTest::mouseClick(newButton, Qt::LeftButton);
    QCOMPARE(listview->count(), 0);

    lineedit->setText(QStringLiteral("foo"));
    QTest::mouseClick(newButton, Qt::LeftButton);
    QCOMPARE(listview->count(), 1);
}

void RecentAddressWidgetTest::shouldDisableAddButton()
{
    PimCommon::RecentAddressWidget w;
    auto *lineedit = w.findChild<QLineEdit *>(QStringLiteral("line_edit"));
    auto *newButton = w.findChild<QToolButton *>(QStringLiteral("new_button"));

    lineedit->setText(QStringLiteral("foo"));
    QVERIFY(newButton->isEnabled());
    lineedit->clear();
    QVERIFY(!newButton->isEnabled());
}

QTEST_MAIN(RecentAddressWidgetTest)
