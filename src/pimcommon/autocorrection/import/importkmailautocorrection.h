/*
  SPDX-FileCopyrightText: 2012-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef IMPORTKMAILAUTOCORRECTION_H
#define IMPORTKMAILAUTOCORRECTION_H

#include "importabstractautocorrection.h"

namespace PimCommon {
class ImportKMailAutocorrection : public ImportAbstractAutocorrection
{
public:
    explicit ImportKMailAutocorrection(QWidget *parent = nullptr);
    ~ImportKMailAutocorrection() override;
    Q_REQUIRED_RESULT bool import(const QString &fileName, ImportAbstractAutocorrection::LoadAttribute loadAttribute = All) override;
};
}

#endif // IMPORTKMAILAUTOCORRECTION_H
