/*
  SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "blacklistakonadisearchemailsearchjob.h"

#include <PIM/contactcompleter.h>
using namespace PimCommon;

BlackListAkonadiSearchEmailSearchJob::BlackListAkonadiSearchEmailSearchJob(QObject *parent)
    : QObject(parent)
{
}

BlackListAkonadiSearchEmailSearchJob::~BlackListAkonadiSearchEmailSearchJob() = default;

bool BlackListAkonadiSearchEmailSearchJob::start()
{
    const QString trimmedString = mSearchEmail.trimmed();
    if (trimmedString.isEmpty()) {
        deleteLater();
        return false;
    }

    const Akonadi::Search::PIM::ContactCompleter com(trimmedString, mLimit);
    Q_EMIT emailsFound(com.complete());
    deleteLater();
    return true;
}

void BlackListAkonadiSearchEmailSearchJob::setSearchEmail(const QString &searchEmail)
{
    mSearchEmail = searchEmail;
}

void BlackListAkonadiSearchEmailSearchJob::setLimit(int limit)
{
    mLimit = qMax(10, limit);
}

#include "moc_blacklistakonadisearchemailsearchjob.cpp"
