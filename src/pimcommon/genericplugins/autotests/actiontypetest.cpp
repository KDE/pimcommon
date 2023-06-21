/*
  SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "actiontypetest.h"
#include <PimCommon/AbstractGenericPluginInterface>
#include <QAction>
#include <QTest>

ActionTypeTest::ActionTypeTest(QObject *parent)
    : QObject(parent)
{
}

ActionTypeTest::~ActionTypeTest() = default;

void ActionTypeTest::shouldHaveDefaultValue()
{
    PimCommon::ActionType actionType;
    QVERIFY(!actionType.action());
    QCOMPARE(actionType.type(), PimCommon::ActionType::Tools);
}

void ActionTypeTest::shouldAssignValue()
{
    auto act = new QAction(nullptr);
    PimCommon::ActionType::Type type = PimCommon::ActionType::File;
    PimCommon::ActionType actionType(act, type);
    QCOMPARE(actionType.action(), act);
    QCOMPARE(actionType.type(), type);
    delete act;
}

QTEST_MAIN(ActionTypeTest)

#include "moc_actiontypetest.cpp"
