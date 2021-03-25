/*
  SPDX-FileCopyrightText: 2012-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "importabstractautocorrection.h"
#include "pimcommon_private_export.h"
namespace PimCommon
{
class PIMCOMMON_TESTS_EXPORT ImportKMailAutocorrection : public ImportAbstractAutocorrection
{
public:
    explicit ImportKMailAutocorrection(QWidget *parent = nullptr);
    ~ImportKMailAutocorrection() override;
    Q_REQUIRED_RESULT bool import(const QString &fileName, ImportAbstractAutocorrection::LoadAttribute loadAttribute = All) override;
};
}

