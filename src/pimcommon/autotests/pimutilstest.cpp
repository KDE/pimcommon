/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "pimutilstest.h"
#include <QTest>
QTEST_GUILESS_MAIN(PimUtilsTest)
PimUtilsTest::PimUtilsTest(QObject *parent)
    : QObject{parent}
{
}

#include "moc_pimutilstest.cpp"
