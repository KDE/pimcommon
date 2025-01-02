/*
  SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/
#include "blacklistbalooemailsearchjobtest.h"
#include "../blacklistakonadisearchemailsearchjob.h"
#include <QTest>

BlackListBalooEmailSearchJobTest::BlackListBalooEmailSearchJobTest(QObject *parent)
    : QObject(parent)
{
}

BlackListBalooEmailSearchJobTest::~BlackListBalooEmailSearchJobTest() = default;

void BlackListBalooEmailSearchJobTest::shouldNotSearchWhenTextIsEmpty()
{
    auto job = new PimCommon::BlackListAkonadiSearchEmailSearchJob;
    QVERIFY(!job->start());
}

QTEST_MAIN(BlackListBalooEmailSearchJobTest)

#include "moc_blacklistbalooemailsearchjobtest.cpp"
