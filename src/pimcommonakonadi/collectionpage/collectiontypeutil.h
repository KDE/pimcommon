/*
  SPDX-FileCopyrightText: 2014-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#pragma once
#include "pimcommonakonadi_export.h"
#include <QByteArray>
#include <QString>

namespace PimCommon
{
/*!
 * \class PimCommon::CollectionTypeUtil
 * \brief The CollectionTypeUtil class provides utilities for collection type handling
 * \inmodule PimCommonAkonadi
 * \inheaderfile PimCommonAkonadi/CollectionTypeUtil
 * \author Laurent Montel <montel@kde.org>
 */
class PIMCOMMONAKONADI_EXPORT CollectionTypeUtil
{
public:
    /*!
     * Constructs a CollectionTypeUtil.
     */
    CollectionTypeUtil();
    /*!
     * Destructs the CollectionTypeUtil.
     */
    ~CollectionTypeUtil();

    /*!
     * Returns the Kolab folder type attribute name.
     * @return The Kolab folder type as a byte array
     */
    static QByteArray kolabFolderType();
    /*!
     * Returns the Kolab incidences-for attribute name.
     * @return The Kolab incidences-for as a byte array
     */
    static QByteArray kolabIncidencesFor();
    /*!
     * Returns the Kolab shared-seen attribute name.
     * @return The Kolab shared-seen as a byte array
     */
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

    /*!
     * Converts a string to an IncidencesFor value.
     * @param string The string to convert
     * @return The corresponding IncidencesFor value
     */
    [[nodiscard]] CollectionTypeUtil::IncidencesFor incidencesForFromString(const QString &string);
    /*!
     * Converts a Kolab type name to a FolderContentsType.
     * @param name The Kolab type name
     * @return The corresponding FolderContentsType
     */
    [[nodiscard]] CollectionTypeUtil::FolderContentsType typeFromKolabName(const QByteArray &name);
    /*!
     * Returns a human-readable description for a folder contents type.
     * @param type The folder contents type
     * @return The description string
     */
    [[nodiscard]] QString folderContentDescription(CollectionTypeUtil::FolderContentsType type);
    /*!
     * Converts a FolderContentsType to a Kolab type name.
     * @param type The folder contents type
     * @return The Kolab type name
     */
    [[nodiscard]] QByteArray kolabNameFromType(CollectionTypeUtil::FolderContentsType type);
    /*!
     * Converts an IncidencesFor value to a string.
     * @param type The IncidencesFor value
     * @return The string representation
     */
    [[nodiscard]] QString incidencesForToString(CollectionTypeUtil::IncidencesFor type);
    /*!
     * Converts a string to a FolderContentsType.
     * @param type The type string
     * @return The corresponding FolderContentsType
     */
    [[nodiscard]] CollectionTypeUtil::FolderContentsType contentsTypeFromString(const QString &type);
    /*!
     * Returns a type name from a Kolab type.
     * @param type The Kolab type
     * @return The type name
     */
    [[nodiscard]] QString typeNameFromKolabType(const QByteArray &type);
    /*!
     * Returns an icon name for a folder contents type.
     * @param type The folder contents type
     * @return The icon name
     */
    [[nodiscard]] QString iconNameFromContentsType(CollectionTypeUtil::FolderContentsType type);
};
}
