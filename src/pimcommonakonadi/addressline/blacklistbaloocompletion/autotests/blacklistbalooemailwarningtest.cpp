/*
  SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "blacklistbalooemailwarningtest.h"
#include "../blacklistbalooemailwarning.h"
#include <QTest>
#include <QSignalSpy>
#include <QAction>

BlackListBalooEmailWarningTest::BlackListBalooEmailWarningTest(QObject *parent)
    : QObject(parent)
{
}

BlackListBalooEmailWarningTest::~BlackListBalooEmailWarningTest()
{
}

void BlackListBalooEmailWarningTest::shouldHaveDefaultValue()
{
    PimCommon::BlackListBalooEmailWarning warning;
    QVERIFY(!warning.isVisible());
    QVERIFY(!warning.isCloseButtonVisible());
    QVERIFY(warning.wordWrap());

    QAction *save = warning.findChild<QAction *>(QStringLiteral("saveblacklist"));
    QVERIFY(save);

    QAction *search = warning.findChild<QAction *>(QStringLiteral("search"));
    QVERIFY(search);
}

void BlackListBalooEmailWarningTest::shouldEmitSaveChanges()
{
    PimCommon::BlackListBalooEmailWarning warning;
    QSignalSpy spy1(&warning, &PimCommon::BlackListBalooEmailWarning::saveChanges);

    QAction *save = warning.findChild<QAction *>(QStringLiteral("saveblacklist"));
    save->trigger();
    QCOMPARE(spy1.count(), 1);
}

void BlackListBalooEmailWarningTest::shouldEmitNewSearch()
{
    PimCommon::BlackListBalooEmailWarning warning;
    QSignalSpy spy1(&warning, &PimCommon::BlackListBalooEmailWarning::newSearch);

    QAction *search = warning.findChild<QAction *>(QStringLiteral("search"));
    search->trigger();
    QCOMPARE(spy1.count(), 1);
}

QTEST_MAIN(BlackListBalooEmailWarningTest)
