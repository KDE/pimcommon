/*
  SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "exportabstractautocorrection.h"
#include "pimcommon_private_export.h"
namespace PimCommon
{
class PIMCOMMON_TESTS_EXPORT ExportLibreOfficeAutocorrection : public ExportAbstractAutocorrection
{
public:
    ExportLibreOfficeAutocorrection();
    ~ExportLibreOfficeAutocorrection() override;

    Q_REQUIRED_RESULT bool exportData(const QString &language, const QString &fileName, QString &errorMessage) override;

private:
    Q_REQUIRED_RESULT bool exportDocumentList();
    Q_REQUIRED_RESULT bool exportSentenceExceptList();
    Q_REQUIRED_RESULT bool exportWordExceptList();
};
}