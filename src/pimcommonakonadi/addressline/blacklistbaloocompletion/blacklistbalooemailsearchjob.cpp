/*
  SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "blacklistbalooemailsearchjob.h"

#include <PIM/contactcompleter.h>
using namespace PimCommon;

BlackListBalooEmailSearchJob::BlackListBalooEmailSearchJob(QObject *parent)
    : QObject(parent)
{
}

BlackListBalooEmailSearchJob::~BlackListBalooEmailSearchJob() = default;

bool BlackListBalooEmailSearchJob::start()
{
    const QString trimmedString = mSearchEmail.trimmed();
    if (trimmedString.isEmpty()) {
        deleteLater();
        return false;
    }

    Akonadi::Search::PIM::ContactCompleter com(trimmedString, mLimit);
    Q_EMIT emailsFound(com.complete());
    deleteLater();
    return true;
}

void BlackListBalooEmailSearchJob::setSearchEmail(const QString &searchEmail)
{
    mSearchEmail = searchEmail;
}

void BlackListBalooEmailSearchJob::setLimit(int limit)
{
    mLimit = qMax(10, limit);
}

#include "moc_blacklistbalooemailsearchjob.cpp"
