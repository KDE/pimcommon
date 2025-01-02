/*
  SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#pragma once

#include "pimcommonakonadi_private_export.h"
#include <KMessageWidget>

namespace PimCommon
{
class PIMCOMMONAKONADI_TESTS_EXPORT BlackListAkonadiSearchEmailWarning : public KMessageWidget
{
    Q_OBJECT
public:
    explicit BlackListAkonadiSearchEmailWarning(QWidget *parent = nullptr);
    ~BlackListAkonadiSearchEmailWarning() override;

Q_SIGNALS:
    void newSearch();
    void saveChanges();

private:
    void slotSaveBlackList();
    void slotSearch();
};
}
