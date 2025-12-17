/*
  SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "blacklistbalooemailwarningtest.h"
#include "../blacklistakonadisearchemailwarning.h"
#include <QAction>
#include <QSignalSpy>
#include <QTest>

BlackListBalooEmailWarningTest::BlackListBalooEmailWarningTest(QObject *parent)
    : QObject(parent)
{
}

BlackListBalooEmailWarningTest::~BlackListBalooEmailWarningTest() = default;

void BlackListBalooEmailWarningTest::shouldHaveDefaultValue()
{
    const PimCommon::BlackListAkonadiSearchEmailWarning warning;
    QVERIFY(!warning.isVisible());
    QVERIFY(!warning.isCloseButtonVisible());
    QVERIFY(warning.wordWrap());

    auto save = warning.findChild<QAction *>(QStringLiteral("saveblacklist"));
    QVERIFY(save);

    auto search = warning.findChild<QAction *>(QStringLiteral("search"));
    QVERIFY(search);

    auto cancelAction = warning.findChild<QAction *>(QStringLiteral("cancel"));
    QVERIFY(cancelAction);
}

void BlackListBalooEmailWarningTest::shouldEmitSaveChanges()
{
    PimCommon::BlackListAkonadiSearchEmailWarning warning;
    QSignalSpy spy1(&warning, &PimCommon::BlackListAkonadiSearchEmailWarning::saveChanges);

    auto save = warning.findChild<QAction *>(QStringLiteral("saveblacklist"));
    save->trigger();
    QCOMPARE(spy1.count(), 1);
}

void BlackListBalooEmailWarningTest::shouldEmitNewSearch()
{
    PimCommon::BlackListAkonadiSearchEmailWarning warning;
    QSignalSpy spy1(&warning, &PimCommon::BlackListAkonadiSearchEmailWarning::newSearch);

    auto search = warning.findChild<QAction *>(QStringLiteral("search"));
    search->trigger();
    QCOMPARE(spy1.count(), 1);
}

QTEST_MAIN(BlackListBalooEmailWarningTest)

#include "moc_blacklistbalooemailwarningtest.cpp"
