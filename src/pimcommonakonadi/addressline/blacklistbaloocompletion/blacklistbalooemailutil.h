/*
  SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#ifndef BLACKLISTBALOOEMAILUTIL_H
#define BLACKLISTBALOOEMAILUTIL_H

#include "pimcommonakonadi_private_export.h"
#include <QStringList>
#include <QHash>
namespace PimCommon {
class PIMCOMMONAKONADI_TESTS_EXPORT BlackListBalooEmailUtil
{
public:
    BlackListBalooEmailUtil();
    ~BlackListBalooEmailUtil();
    void initialBlackList(const QStringList &blackList);
    void newBlackList(const QHash<QString, bool> &);
    Q_REQUIRED_RESULT QStringList createNewBlackList();
private:
    QStringList mInitialList;
    QHash<QString, bool> mNewBlackList;
};
}
#endif // BLACKLISTBALOOEMAILUTIL_H
