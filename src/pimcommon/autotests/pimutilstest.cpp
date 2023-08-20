/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "pimutilstest.h"
#include "util/pimutil.h"
#include <QTest>
QTEST_GUILESS_MAIN(PimUtilsTest)
PimUtilsTest::PimUtilsTest(QObject *parent)
    : QObject{parent}
{
}

void PimUtilsTest::shouldTestInvokeHelp()
{
    QCOMPARE(PimCommon::Util::generateHelpUrl(QStringLiteral("kmail2/configure-identity.html")), QUrl(QStringLiteral("help:/kmail2/configure-identity.html")));
    QCOMPARE(PimCommon::Util::generateHelpUrl(QStringLiteral("kmail2/configure-identity.html"), QStringLiteral("configure-identity-newidentitydialog")),
             QUrl(QStringLiteral("help:/kmail2/configure-identity.html?anchor=configure-identity-newidentitydialog")));
}

#include "moc_pimutilstest.cpp"
