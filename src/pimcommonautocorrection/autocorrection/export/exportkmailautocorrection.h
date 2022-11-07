/*
  SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "exportabstractautocorrection.h"

#include "pimcommonautocorrection_private_export.h"
namespace PimCommonAutoCorrection
{
class PIMCOMMONAUTOCORRECTION_TESTS_EXPORT ExportKMailAutocorrection : public ExportAbstractAutocorrection
{
public:
    ExportKMailAutocorrection();
    ~ExportKMailAutocorrection() override;

    Q_REQUIRED_RESULT bool exportData(const QString &language, const QString &fileName, QString &errorMessage) override;
};
}
