/*
  SPDX-FileCopyrightText: 2015-2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "blacklistbalooemailutil.h"

using namespace PimCommon;
BlackListBalooEmailUtil::BlackListBalooEmailUtil() = default;

BlackListBalooEmailUtil::~BlackListBalooEmailUtil() = default;

void BlackListBalooEmailUtil::initialBlackList(const QStringList &blackList)
{
    mInitialList = blackList;
}

void BlackListBalooEmailUtil::newBlackList(const QHash<QString, bool> &list)
{
    mNewBlackList = list;
}

QStringList BlackListBalooEmailUtil::createNewBlackList()
{
    if (mNewBlackList.isEmpty()) {
        return mInitialList;
    }

    QHashIterator<QString, bool> i(mNewBlackList);
    while (i.hasNext()) {
        i.next();
        const QString newEmail(i.key());
        if (i.value()) {
            if (!mInitialList.contains(newEmail)) {
                mInitialList.append(newEmail);
            }
        } else {
            mInitialList.removeAll(newEmail);
        }
    }
    return mInitialList;
}
