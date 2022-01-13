/*
 * SPDX-FileCopyrightText: 2010 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
 * SPDX-FileCopyrightText: 2010 Tobias Koenig <tokoe@kdab.com>
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "aclutils_p.h"

#include <KLazyLocalizedString>
#include <KLocalizedString>

using namespace PimCommon;

static const struct {
    KIMAP::Acl::Rights permissions;
    const KLazyLocalizedString userString;
} standardPermissions[] = {
    {KIMAP::Acl::None, kli18nc("Permissions", "None")},

    {KIMAP::Acl::Lookup | KIMAP::Acl::Read | KIMAP::Acl::KeepSeen, kli18nc("Permissions", "Read")},

    {KIMAP::Acl::Lookup | KIMAP::Acl::Read | KIMAP::Acl::KeepSeen | KIMAP::Acl::Insert | KIMAP::Acl::Post, kli18nc("Permissions", "Append")},

    {KIMAP::Acl::Lookup | KIMAP::Acl::Read | KIMAP::Acl::KeepSeen | KIMAP::Acl::Insert | KIMAP::Acl::Post | KIMAP::Acl::Write | KIMAP::Acl::CreateMailbox
         | KIMAP::Acl::DeleteMailbox | KIMAP::Acl::DeleteMessage | KIMAP::Acl::Expunge,
     kli18nc("Permissions", "Write")},

    {KIMAP::Acl::Lookup | KIMAP::Acl::Read | KIMAP::Acl::KeepSeen | KIMAP::Acl::Insert | KIMAP::Acl::Post | KIMAP::Acl::Write | KIMAP::Acl::CreateMailbox
         | KIMAP::Acl::DeleteMailbox | KIMAP::Acl::DeleteMessage | KIMAP::Acl::Expunge | KIMAP::Acl::Admin,
     kli18nc("Permissions", "All")}};

uint AclUtils::standardPermissionsCount()
{
    return sizeof(standardPermissions) / sizeof(*standardPermissions);
}

KIMAP::Acl::Rights AclUtils::permissionsForIndex(uint index)
{
    Q_ASSERT(index < standardPermissionsCount());

    return standardPermissions[index].permissions;
}

int AclUtils::indexForPermissions(KIMAP::Acl::Rights permissions)
{
    const uint maxSize(sizeof(standardPermissions) / sizeof(*standardPermissions));
    for (uint i = 0; i < maxSize; ++i) {
        if (KIMAP::Acl::normalizedRights(permissions) == standardPermissions[i].permissions) {
            return i;
        }
    }

    return -1;
}

QString AclUtils::permissionsToUserString(KIMAP::Acl::Rights permissions)
{
    const uint maxSize(sizeof(standardPermissions) / sizeof(*standardPermissions));
    for (uint i = 0; i < maxSize; ++i) {
        if (KIMAP::Acl::normalizedRights(permissions) == standardPermissions[i].permissions) {
            return KLocalizedString(standardPermissions[i].userString).toString();
        }
    }

    return i18n("Custom Permissions (%1)", QString::fromLatin1(KIMAP::Acl::rightsToString(permissions)));
}

QString AclUtils::guessUserName(const QString &loginName, const QString &serverName)
{
    int pos = loginName.indexOf(QLatin1Char('@'));
    if (pos != -1) {
        // strip of the domain part and use user name only
        return loginName.left(pos);
    } else {
        pos = serverName.lastIndexOf(QLatin1Char('.'));
        if (pos == -1) { // no qualified domain name, only hostname
            return QStringLiteral("%1@%2").arg(loginName, serverName);
        }

        pos = serverName.lastIndexOf(QLatin1Char('.'), pos - 1);
        if (pos == -1) { // a simple domain name e.g. mydomain.org
            return QStringLiteral("%1@%2").arg(loginName, serverName);
        } else {
            return QStringLiteral("%1@%2").arg(loginName, serverName.mid(pos + 1));
        }
    }
}
