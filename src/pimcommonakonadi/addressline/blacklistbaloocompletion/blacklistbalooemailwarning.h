/*
  SPDX-FileCopyrightText: 2015-2024 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#pragma once

#include "pimcommonakonadi_private_export.h"
#include <KMessageWidget>

namespace PimCommon
{
class PIMCOMMONAKONADI_TESTS_EXPORT BlackListBalooEmailWarning : public KMessageWidget
{
    Q_OBJECT
public:
    explicit BlackListBalooEmailWarning(QWidget *parent = nullptr);
    ~BlackListBalooEmailWarning() override;

Q_SIGNALS:
    void newSearch();
    void saveChanges();

private:
    void slotSaveBlackList();
    void slotSearch();
};
}
