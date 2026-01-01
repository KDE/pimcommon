/*
  SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "blacklistakonadisearchemailutil.h"

using namespace PimCommon;
BlackListAkonadiSearchEmailUtil::BlackListAkonadiSearchEmailUtil() = default;

BlackListAkonadiSearchEmailUtil::~BlackListAkonadiSearchEmailUtil() = default;

void BlackListAkonadiSearchEmailUtil::initialBlackList(const QStringList &blackList)
{
    mInitialList = blackList;
}

void BlackListAkonadiSearchEmailUtil::setNewBlackList(const QHash<QString, bool> &list)
{
    mNewBlackList = list;
}

QStringList BlackListAkonadiSearchEmailUtil::createNewBlackList()
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
