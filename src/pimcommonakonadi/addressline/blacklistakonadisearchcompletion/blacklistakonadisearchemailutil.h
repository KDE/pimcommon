/*
  SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#pragma once

#include "pimcommonakonadi_private_export.h"
#include <QHash>
#include <QStringList>
namespace PimCommon
{
class PIMCOMMONAKONADI_TESTS_EXPORT BlackListAkonadiSearchEmailUtil
{
public:
    BlackListAkonadiSearchEmailUtil();
    ~BlackListAkonadiSearchEmailUtil();
    void initialBlackList(const QStringList &blackList);
    void setNewBlackList(const QHash<QString, bool> &);
    [[nodiscard]] QStringList createNewBlackList();

private:
    QStringList mInitialList;
    QHash<QString, bool> mNewBlackList;
};
}
