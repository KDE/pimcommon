/*
  SPDX-FileCopyrightText: 2014-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "collectiontypeutil.h"

#include <KLocalizedString>

using namespace Qt::Literals::StringLiterals;
using namespace PimCommon;
CollectionTypeUtil::CollectionTypeUtil() = default;

CollectionTypeUtil::~CollectionTypeUtil() = default;

QByteArray CollectionTypeUtil::kolabFolderType()
{
    return "/shared/vendor/kolab/folder-type";
}

QByteArray CollectionTypeUtil::kolabIncidencesFor()
{
    return "/shared/vendor/kolab/incidences-for";
}

QByteArray CollectionTypeUtil::kolabSharedSeen()
{
    return "/shared/vendor/cmu/cyrus-imapd/sharedseen";
}

QString CollectionTypeUtil::folderContentDescription(CollectionTypeUtil::FolderContentsType type)
{
    switch (type) {
    case CollectionTypeUtil::ContentsTypeMail:
        return i18nc("type of folder content", "Mail");
    case CollectionTypeUtil::ContentsTypeCalendar:
        return i18nc("type of folder content", "Calendar");
    case CollectionTypeUtil::ContentsTypeContact:
        return i18nc("type of folder content", "Contacts");
    case CollectionTypeUtil::ContentsTypeNote:
        return i18nc("type of folder content", "Notes");
    case CollectionTypeUtil::ContentsTypeTask:
        return i18nc("type of folder content", "Tasks");
    case CollectionTypeUtil::ContentsTypeJournal:
        return i18nc("type of folder content", "Journal");
    case CollectionTypeUtil::ContentsTypeConfiguration:
        return i18nc("type of folder content", "Configuration");
    case CollectionTypeUtil::ContentsTypeFreebusy:
        return i18nc("type of folder content", "Freebusy");
    case CollectionTypeUtil::ContentsTypeFile:
        return i18nc("type of folder content", "Files");
    default:
        return i18nc("type of folder content", "Unknown");
    }
}

QString CollectionTypeUtil::incidencesForToString(CollectionTypeUtil::IncidencesFor type)
{
    switch (type) {
    case CollectionTypeUtil::IncForNobody:
        return QStringLiteral("nobody");
    case CollectionTypeUtil::IncForAdmins:
        return QStringLiteral("admins");
    case CollectionTypeUtil::IncForReaders:
        return QStringLiteral("readers");
    }

    return {}; // can't happen
}

CollectionTypeUtil::IncidencesFor CollectionTypeUtil::incidencesForFromString(const QString &string)
{
    if (string == "nobody"_L1) {
        return CollectionTypeUtil::IncForNobody;
    } else if (string == "admins"_L1) {
        return CollectionTypeUtil::IncForAdmins;
    } else if (string == "readers"_L1) {
        return CollectionTypeUtil::IncForReaders;
    }

    return CollectionTypeUtil::IncForAdmins; // by default
}

CollectionTypeUtil::FolderContentsType CollectionTypeUtil::typeFromKolabName(const QByteArray &name)
{
    if (name == "task" || name == "task.default") {
        return CollectionTypeUtil::ContentsTypeTask;
    }
    if (name == "event" || name == "event.default") {
        return CollectionTypeUtil::ContentsTypeCalendar;
    }
    if (name == "contact" || name == "contact.default") {
        return CollectionTypeUtil::ContentsTypeContact;
    }
    if (name == "note" || name == "note.default") {
        return CollectionTypeUtil::ContentsTypeNote;
    }
    if (name == "journal" || name == "journal.default") {
        return CollectionTypeUtil::ContentsTypeJournal;
    }
    if (name == "configuration" || name == "configuration.default") {
        return CollectionTypeUtil::ContentsTypeConfiguration;
    }
    if (name == "freebusy" || name == "freebusy.default") {
        return CollectionTypeUtil::ContentsTypeFreebusy;
    }
    if (name == "file" || name == "file.default") {
        return CollectionTypeUtil::ContentsTypeFile;
    }

    return CollectionTypeUtil::ContentsTypeMail;
}

QByteArray CollectionTypeUtil::kolabNameFromType(CollectionTypeUtil::FolderContentsType type)
{
    switch (type) {
    case CollectionTypeUtil::ContentsTypeCalendar:
        return "event";
    case CollectionTypeUtil::ContentsTypeContact:
        return "contact";
    case CollectionTypeUtil::ContentsTypeNote:
        return "note";
    case CollectionTypeUtil::ContentsTypeTask:
        return "task";
    case CollectionTypeUtil::ContentsTypeJournal:
        return "journal";
    case CollectionTypeUtil::ContentsTypeConfiguration:
        return "configuration";
    case CollectionTypeUtil::ContentsTypeFreebusy:
        return "freebusy";
    case CollectionTypeUtil::ContentsTypeFile:
        return "file";
    default:
        return {};
    }
}

CollectionTypeUtil::FolderContentsType CollectionTypeUtil::contentsTypeFromString(const QString &type)
{
    if (type == i18nc("type of folder content", "Mail")) {
        return CollectionTypeUtil::ContentsTypeMail;
    }
    if (type == i18nc("type of folder content", "Calendar")) {
        return CollectionTypeUtil::ContentsTypeCalendar;
    }
    if (type == i18nc("type of folder content", "Contacts")) {
        return CollectionTypeUtil::ContentsTypeContact;
    }
    if (type == i18nc("type of folder content", "Notes")) {
        return CollectionTypeUtil::ContentsTypeNote;
    }
    if (type == i18nc("type of folder content", "Tasks")) {
        return CollectionTypeUtil::ContentsTypeTask;
    }
    if (type == i18nc("type of folder content", "Journal")) {
        return CollectionTypeUtil::ContentsTypeJournal;
    }
    if (type == i18nc("type of folder content", "Configuration")) {
        return CollectionTypeUtil::ContentsTypeConfiguration;
    }
    if (type == i18nc("type of folder content", "Freebusy")) {
        return CollectionTypeUtil::ContentsTypeFreebusy;
    }
    if (type == i18nc("type of folder content", "Files")) {
        return CollectionTypeUtil::ContentsTypeFile;
    }

    return CollectionTypeUtil::ContentsTypeMail; // safety return value
}

QString CollectionTypeUtil::typeNameFromKolabType(const QByteArray &type)
{
    if (type == "task" || type == "task.default") {
        return i18nc("type of folder content", "Tasks");
    }
    if (type == "event" || type == "event.default") {
        return i18nc("type of folder content", "Calendar");
    }
    if (type == "contact" || type == "contact.default") {
        return i18nc("type of folder content", "Contacts");
    }
    if (type == "note" || type == "note.default") {
        return i18nc("type of folder content", "Notes");
    }
    if (type == "journal" || type == "journal.default") {
        return i18nc("type of folder content", "Journal");
    }
    if (type == "configuration" || type == "configuration.default") {
        return i18nc("type of folder content", "Configuration");
    }
    if (type == "freebusy" || type == "freebusy.default") {
        return i18nc("type of folder content", "Freebusy");
    }
    if (type == "file" || type == "file.default") {
        return i18nc("type of folder content", "Files");
    }

    return i18nc("type of folder content", "Mail");
}

QString CollectionTypeUtil::iconNameFromContentsType(CollectionTypeUtil::FolderContentsType type)
{
    QString iconName;
    switch (type) {
    case CollectionTypeUtil::ContentsTypeCalendar:
        iconName = QStringLiteral("view-calendar");
        break;
    case CollectionTypeUtil::ContentsTypeContact:
        iconName = QStringLiteral("view-pim-contacts");
        break;
    case CollectionTypeUtil::ContentsTypeNote:
        iconName = QStringLiteral("view-pim-notes");
        break;
    case CollectionTypeUtil::ContentsTypeTask:
        iconName = QStringLiteral("view-pim-tasks");
        break;
    case CollectionTypeUtil::ContentsTypeJournal:
        iconName = QStringLiteral("view-pim-journal");
        break;
    case CollectionTypeUtil::ContentsTypeConfiguration:
        iconName = QStringLiteral("configure");
        break;
    case CollectionTypeUtil::ContentsTypeFreebusy:
        iconName = QStringLiteral("view-calendar-agenda");
        break;
    case CollectionTypeUtil::ContentsTypeFile:
        iconName = QStringLiteral("document-open");
        break;
    case CollectionTypeUtil::ContentsTypeMail:
    default:
        break;
    }

    return iconName;
}
