/*
  Copyright (c) 2015-2019 Montel Laurent <montel@kde.org>

  This library is free software; you can redistribute it and/or modify it
  under the terms of the GNU Library General Public License as published by
  the Free Software Foundation; either version 2 of the License, or (at your
  option) any later version.

  This library is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
  License for more details.

  You should have received a copy of the GNU Library General Public License
  along with this library; see the file COPYING.LIB.  If not, write to the
  Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
  02110-1301, USA.

*/

#include "fetchrecursivecollectionsjob.h"
#include "pimcommonakonadi_debug.h"
#include <CollectionFetchJob>
#include <AkonadiCore/CollectionFetchScope>
using namespace PimCommon;

class PimCommon::FetchRecursiveCollectionsJobPrivate
{
public:
    FetchRecursiveCollectionsJobPrivate()
    {
    }

    Akonadi::Collection mTopCollection;
};

FetchRecursiveCollectionsJob::FetchRecursiveCollectionsJob(QObject *parent)
    : QObject(parent)
    , d(new PimCommon::FetchRecursiveCollectionsJobPrivate)
{
}

FetchRecursiveCollectionsJob::~FetchRecursiveCollectionsJob()
{
    delete d;
}

void FetchRecursiveCollectionsJob::start()
{
    if (!d->mTopCollection.isValid()) {
        qCWarning(PIMCOMMONAKONADI_LOG) << "Any collection is defined";
        Q_EMIT fetchCollectionFailed();
        deleteLater();
        return;
    }
    Akonadi::CollectionFetchJob *job = new Akonadi::CollectionFetchJob(d->mTopCollection, Akonadi::CollectionFetchJob::Recursive);
    job->fetchScope().setAncestorRetrieval(Akonadi::CollectionFetchScope::All);
    connect(job, &Akonadi::CollectionFetchJob::result, this, &FetchRecursiveCollectionsJob::slotInitialCollectionFetchingDone);
}

void FetchRecursiveCollectionsJob::setTopCollection(const Akonadi::Collection &col)
{
    d->mTopCollection = col;
}

void FetchRecursiveCollectionsJob::slotInitialCollectionFetchingDone(KJob *job)
{
    if (job->error()) {
        qCWarning(PIMCOMMONAKONADI_LOG) << job->errorString();
        Q_EMIT fetchCollectionFailed();
        deleteLater();
        return;
    }
    Akonadi::CollectionFetchJob *fetchJob = qobject_cast<Akonadi::CollectionFetchJob *>(job);
    Q_EMIT fetchCollectionFinished(fetchJob->collections() << d->mTopCollection);
    deleteLater();
}
