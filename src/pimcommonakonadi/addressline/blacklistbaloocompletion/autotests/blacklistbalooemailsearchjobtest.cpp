/*
  SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/
#include "blacklistbalooemailsearchjobtest.h"
#include "../blacklistbalooemailsearchjob.h"
#include <QTest>

BlackListBalooEmailSearchJobTest::BlackListBalooEmailSearchJobTest(QObject *parent)
    : QObject(parent)
{
}

BlackListBalooEmailSearchJobTest::~BlackListBalooEmailSearchJobTest()
{
}

void BlackListBalooEmailSearchJobTest::shouldNotSearchWhenTextIsEmpty()
{
    auto *job = new PimCommon::BlackListBalooEmailSearchJob;
    QVERIFY(!job->start());
}

QTEST_MAIN(BlackListBalooEmailSearchJobTest)
