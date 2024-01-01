/*
   SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "addresseelineeditbalootest.h"
#include "addressline/addresslineedit/addresseelineeditbaloo.h"
#include <QStandardPaths>
#include <QTest>
QTEST_MAIN(AddresseeLineEditBalooTest)

AddresseeLineEditBalooTest::AddresseeLineEditBalooTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void AddresseeLineEditBalooTest::shouldHaveDefaultValues()
{
    PimCommon::AddresseeLineEditBaloo b;
    QVERIFY(b.balooBlackList().isEmpty());
    QVERIFY(b.domainExcludeList().isEmpty());
    QCOMPARE(b.balooCompletionSource(), 0);
}

#include "moc_addresseelineeditbalootest.cpp"
