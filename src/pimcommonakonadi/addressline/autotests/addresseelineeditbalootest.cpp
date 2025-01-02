/*
   SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "addresseelineeditbalootest.h"
#include "addressline/addresslineedit/addresseelineeditakonadisearch.h"
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
    PimCommon::AddresseeLineEditAkonadiSearch b;
    QVERIFY(b.akonadiSearchBlackList().isEmpty());
    QVERIFY(b.domainExcludeList().isEmpty());
    QCOMPARE(b.akonadiSearchCompletionSource(), 0);
}

#include "moc_addresseelineeditbalootest.cpp"
