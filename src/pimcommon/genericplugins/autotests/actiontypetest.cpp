/*
  Copyright (c) 2015-2017 Montel Laurent <montel@kde.org>

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

#include "actiontypetest.h"
#include <PimCommonAkonadi/GenericPluginInterface>
#include <QAction>
#include <QTest>

ActionTypeTest::ActionTypeTest(QObject *parent)
    : QObject(parent)
{

}

ActionTypeTest::~ActionTypeTest()
{

}

void ActionTypeTest::shouldHaveDefaultValue()
{
    PimCommon::ActionType actionType;
    QVERIFY(!actionType.action());
    QCOMPARE(actionType.type(), PimCommon::ActionType::Tools);
}

void ActionTypeTest::shouldAssignValue()
{
    QAction *act = new QAction(nullptr);
    PimCommon::ActionType::Type type = PimCommon::ActionType::File;
    PimCommon::ActionType actionType(act, type);
    QCOMPARE(actionType.action(), act);
    QCOMPARE(actionType.type(), type);
}

QTEST_MAIN(ActionTypeTest)
