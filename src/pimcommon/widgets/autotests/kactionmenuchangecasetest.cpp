/*
  SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "kactionmenuchangecasetest.h"
#include "../src/pimcommon/widgets/kactionmenuchangecase.h"
#include <QMenu>
#include <QSignalSpy>
#include <QTest>
using namespace PimCommon;
KActionMenuChangeCaseTest::KActionMenuChangeCaseTest(QObject *parent)
    : QObject(parent)
{
}

KActionMenuChangeCaseTest::~KActionMenuChangeCaseTest() = default;

void KActionMenuChangeCaseTest::shouldHaveDefaultValue()
{
    KActionMenuChangeCase menu;
    QVERIFY(menu.upperCaseAction());
    QVERIFY(menu.sentenceCaseAction());
    QVERIFY(menu.lowerCaseAction());
    QVERIFY(menu.reverseCaseAction());
    QCOMPARE(menu.menu()->actions().count(), 4);
}

void KActionMenuChangeCaseTest::shouldEmitSignals()
{
    KActionMenuChangeCase menu;
    QSignalSpy spyUpper(&menu, &KActionMenuChangeCase::upperCase);
    QSignalSpy spyLower(&menu, &KActionMenuChangeCase::lowerCase);
    QSignalSpy spySentence(&menu, &KActionMenuChangeCase::sentenceCase);
    QSignalSpy spyReverse(&menu, &KActionMenuChangeCase::reverseCase);
    menu.upperCaseAction()->trigger();
    menu.lowerCaseAction()->trigger();
    menu.sentenceCaseAction()->trigger();
    menu.reverseCaseAction()->trigger();
    QCOMPARE(spyUpper.count(), 1);
    QCOMPARE(spyLower.count(), 1);
    QCOMPARE(spySentence.count(), 1);
    QCOMPARE(spyReverse.count(), 1);
}

QTEST_MAIN(KActionMenuChangeCaseTest)
