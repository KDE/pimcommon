/*
  SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "deeplengineconfiguredialogtest.h"
#include "../deeplengineconfiguredialog.h"
#include <QTest>
QTEST_MAIN(DeeplEngineConfigureDialogTest)
DeeplEngineConfigureDialogTest::DeeplEngineConfigureDialogTest(QObject *parent)
    : QObject{parent}
{
}

void DeeplEngineConfigureDialogTest::shouldHaveDefaultValues()
{
    DeeplEngineConfigureDialog d;
    // TODO
}
