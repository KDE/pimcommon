/*
  SPDX-FileCopyrightText: 2014-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#pragma once
#include "pimcommonakonadi_export.h"
#include <QByteArray>
#include <QString>

namespace PimCommon
{
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
        IncForReaders,
    };

    [[nodiscard]] CollectionTypeUtil::IncidencesFor incidencesForFromString(const QString &string);
    [[nodiscard]] CollectionTypeUtil::FolderContentsType typeFromKolabName(const QByteArray &name);
    [[nodiscard]] QString folderContentDescription(CollectionTypeUtil::FolderContentsType type);
    [[nodiscard]] QByteArray kolabNameFromType(CollectionTypeUtil::FolderContentsType type);
    [[nodiscard]] QString incidencesForToString(CollectionTypeUtil::IncidencesFor type);
    [[nodiscard]] CollectionTypeUtil::FolderContentsType contentsTypeFromString(const QString &type);
    [[nodiscard]] QString typeNameFromKolabType(const QByteArray &type);
    [[nodiscard]] QString iconNameFromContentsType(CollectionTypeUtil::FolderContentsType type);
};
}
