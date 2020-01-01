/*
  Copyright (c) 2015-2020 Laurent Montel <montel@kde.org>

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

#ifndef FETCHRECURSIVECOLLECTIONSJOB_H
#define FETCHRECURSIVECOLLECTIONSJOB_H

#include <Collection>
#include <QObject>
#include "pimcommonakonadi_export.h"
class KJob;
namespace PimCommon {
class FetchRecursiveCollectionsJobPrivate;
/**
 * @brief The FetchRecursiveCollectionsJob class
 * @author Laurent Montel <montel@kde.org>
 */
class PIMCOMMONAKONADI_EXPORT FetchRecursiveCollectionsJob : public QObject
{
    Q_OBJECT
public:
    explicit FetchRecursiveCollectionsJob(QObject *parent = nullptr);
    ~FetchRecursiveCollectionsJob();

    void setTopCollection(const Akonadi::Collection &col);

    void start();

Q_SIGNALS:
    void fetchCollectionFinished(const Akonadi::Collection::List &list);
    void fetchCollectionFailed();

private:
    void slotInitialCollectionFetchingDone(KJob *job);
    FetchRecursiveCollectionsJobPrivate *const d;
};
}
#endif // FETCHRECURSIVECOLLECTIONSJOB_H
