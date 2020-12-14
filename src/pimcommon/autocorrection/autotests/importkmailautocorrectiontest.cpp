/*
  SPDX-FileCopyrightText: 2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "importkmailautocorrectiontest.h"
#include "autocorrection/import/importkmailautocorrection.h"
#include <QTest>
QTEST_MAIN(ImportKMailAutocorrectionTest)

ImportKMailAutocorrectionTest::ImportKMailAutocorrectionTest(QObject *parent)
    : QObject(parent)
{

}

void ImportKMailAutocorrectionTest::shouldHaveDefaultValues()
{
    PimCommon::ImportKMailAutocorrection import;
    //TODO
}
