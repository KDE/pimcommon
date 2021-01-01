/*
  SPDX-FileCopyrightText: 2014-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#ifndef COLLECTIONTYPEUTIL_H
#define COLLECTIONTYPEUTIL_H
#include "pimcommonakonadi_export.h"
#include <QByteArray>
#include <QString>

namespace PimCommon {
/**
 * @brief The CollectionTypeUtil class
 * @author Laurent Montel <montel@kde.org>
 */
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
