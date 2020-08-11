/*
  SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#ifndef BLACKLISTBALOOEMAILWARNING_H
#define BLACKLISTBALOOEMAILWARNING_H

#include <KMessageWidget>
#include "pimcommonakonadi_private_export.h"

namespace PimCommon {
class PIMCOMMONAKONADI_TESTS_EXPORT BlackListBalooEmailWarning : public KMessageWidget
{
    Q_OBJECT
public:
    explicit BlackListBalooEmailWarning(QWidget *parent = nullptr);
    ~BlackListBalooEmailWarning();

Q_SIGNALS:
    void newSearch();
    void saveChanges();

private:
    void slotSaveBlackList();
    void slotSearch();
};
}
#endif // BLACKLISTBALOOEMAILWARNING_H
