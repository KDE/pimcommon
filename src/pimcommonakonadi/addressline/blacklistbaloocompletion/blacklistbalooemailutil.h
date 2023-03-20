/*
  SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#pragma once

#include "pimcommonakonadi_private_export.h"
#include <QHash>
#include <QStringList>
namespace PimCommon
{
class PIMCOMMONAKONADI_TESTS_EXPORT BlackListBalooEmailUtil
{
public:
    BlackListBalooEmailUtil();
    ~BlackListBalooEmailUtil();
    void initialBlackList(const QStringList &blackList);
    void setNewBlackList(const QHash<QString, bool> &);
    Q_REQUIRED_RESULT QStringList createNewBlackList();

private:
    QStringList mInitialList;
    QHash<QString, bool> mNewBlackList;
};
}
