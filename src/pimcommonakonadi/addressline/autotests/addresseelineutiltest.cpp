/*
   SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "addresseelineutiltest.h"
#include "addressline/addresseelineutil.h"
#include <QTest>
QTEST_GUILESS_MAIN(AddresseeLineUtilTest)
using namespace Qt::Literals::StringLiterals;
AddresseeLineUtilTest::AddresseeLineUtilTest(QObject *parent)
    : QObject{parent}
{
}

void AddresseeLineUtilTest::shouldHaveDefaultValues()
{
    QCOMPARE(PimCommon::AddresseeLineUtil::excludeEmailsRegularExpression(), QStringList({u"no.?reply.*@"_s, u"@noreply"_s}));
}
