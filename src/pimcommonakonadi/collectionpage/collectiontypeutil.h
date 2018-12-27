/*
  Copyright (c) 2014-2019 Montel Laurent <montel@kde.org>

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

#ifndef COLLECTIONTYPEUTIL_H
#define COLLECTIONTYPEUTIL_H
#include "pimcommonakonadi_export.h"
#include <QByteArray>
#include <QString>

namespace PimCommon {
class PIMCOMMONAKONADI_EXPORT CollectionTypeUtil
{
public:
    CollectionTypeUtil();
    ~CollectionTypeUtil();

    static QByteArray kolabFolderType();
    static QByteArray kolabIncidencesFor();
    static QByteArray kolabSharedSeen();

    enum FolderContentsType {
        ContentsTypeMail = 0,
        ContentsTypeCalendar,
        ContentsTypeContact,
        ContentsTypeNote,
        ContentsTypeTask,
        ContentsTypeJournal,
        ContentsTypeConfiguration,
        ContentsTypeFreebusy,
        ContentsTypeFile,
        ContentsTypeLast = ContentsTypeFile
    };

    enum IncidencesFor {
        IncForNobody,
        IncForAdmins,
        IncForReaders
    };

    Q_REQUIRED_RESULT CollectionTypeUtil::IncidencesFor incidencesForFromString(const QString &string);
    Q_REQUIRED_RESULT CollectionTypeUtil::FolderContentsType typeFromKolabName(const QByteArray &name);
    Q_REQUIRED_RESULT QString folderContentDescription(CollectionTypeUtil::FolderContentsType type);
    Q_REQUIRED_RESULT QByteArray kolabNameFromType(CollectionTypeUtil::FolderContentsType type);
    Q_REQUIRED_RESULT QString incidencesForToString(CollectionTypeUtil::IncidencesFor type);
    Q_REQUIRED_RESULT CollectionTypeUtil::FolderContentsType contentsTypeFromString(const QString &type);
    Q_REQUIRED_RESULT QString typeNameFromKolabType(const QByteArray &type);
    Q_REQUIRED_RESULT QString iconNameFromContentsType(CollectionTypeUtil::FolderContentsType type);
};
}
#endif // COLLECTIONTYPEUTIL_H
