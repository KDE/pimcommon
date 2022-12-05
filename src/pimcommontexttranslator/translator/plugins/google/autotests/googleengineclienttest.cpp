/*
  SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "googleengineclienttest.h"
#include "../googleengineclient.h"
#include <QTest>
QTEST_MAIN(GoogleEngineClientTest)

GoogleEngineClientTest::GoogleEngineClientTest(QObject *parent)
    : QObject{parent}
{
}

void GoogleEngineClientTest::shouldHaveDefaultValues()
{
    GoogleEngineClient client;
    QCOMPARE(client.name(), QStringLiteral("google"));
    QVERIFY(client.createTranslator());
    QVERIFY(!client.supportedLanguages().isEmpty());
}
