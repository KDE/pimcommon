/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "needupdateparsehtmlutiltest.h"
#include "needupdateversion/needupdateparsehtmlutil.h"
#include <QTest>

QTEST_MAIN(NeedUpdateParseHtmlUtilTest)

NeedUpdateParseHtmlUtilTest::NeedUpdateParseHtmlUtilTest(QObject *parent)
    : QObject{parent}
{
}

void NeedUpdateParseHtmlUtilTest::shouldExtraDate()
{
    QFETCH(QString, name);
    QFETCH(QString, dateStr);

    const QString originalJsonFile = QLatin1StringView(PIMCOMMON_DATA_NEEDUPDATEDIR) + QStringLiteral("/") + name + QStringLiteral(".html");

    QFile f(originalJsonFile);
    [&]() {
        QVERIFY(f.open(QIODevice::ReadOnly));
    }();
    const auto content = f.readAll();
    f.close();

    QCOMPARE(PimCommon::NeedUpdateParseHtmlUtil::extractDate(QString::fromUtf8(content)), dateStr);
}

void NeedUpdateParseHtmlUtilTest::shouldExtraDate_data()
{
    QTest::addColumn<QString>("name");
    QTest::addColumn<QString>("dateStr");

    QTest::addRow("test1") << QStringLiteral("test1") << QStringLiteral("2024-12-28");
}

#include "moc_needupdateparsehtmlutiltest.cpp"
