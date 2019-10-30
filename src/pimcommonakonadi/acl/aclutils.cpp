/*
 * Copyright (c) 2010 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
 * Copyright (c) 2010 Tobias Koenig <tokoe@kdab.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include "aclutils_p.h"

#include <KLocalizedString>

using namespace PimCommon;

static const struct {
    KIMAP::Acl::Rights permissions;
    const char *context;
    const char *userString;
} standardPermissions[] = {
    {
        KIMAP::Acl::None,
        I18NC_NOOP("Permissions", "None")
    },

    {
        KIMAP::Acl::Lookup | KIMAP::Acl::Read | KIMAP::Acl::KeepSeen,
        I18NC_NOOP("Permissions", "Read")
    },

    {
        KIMAP::Acl::Lookup | KIMAP::Acl::Read | KIMAP::Acl::KeepSeen
        |KIMAP::Acl::Insert | KIMAP::Acl::Post,
        I18NC_NOOP("Permissions", "Append")
    },

    {
        KIMAP::Acl::Lookup | KIMAP::Acl::Read | KIMAP::Acl::KeepSeen
        |KIMAP::Acl::Insert | KIMAP::Acl::Post | KIMAP::Acl::Write
        |KIMAP::Acl::CreateMailbox | KIMAP::Acl::DeleteMailbox
        |KIMAP::Acl::DeleteMessage | KIMAP::Acl::Expunge,
        I18NC_NOOP("Permissions", "Write")
    },

    {
        KIMAP::Acl::Lookup | KIMAP::Acl::Read | KIMAP::Acl::KeepSeen
        |KIMAP::Acl::Insert | KIMAP::Acl::Post | KIMAP::Acl::Write
        |KIMAP::Acl::CreateMailbox | KIMAP::Acl::DeleteMailbox
        |KIMAP::Acl::DeleteMessage | KIMAP::Acl::Expunge | KIMAP::Acl::Admin,
        I18NC_NOOP("Permissions", "All")
    }
};

uint AclUtils::standardPermissionsCount()
{
    return sizeof(standardPermissions) / sizeof(*standardPermissions);
}

KIMAP::Acl::Rights AclUtils::permissionsForIndex(uint index)
{
    Q_ASSERT(index < standardPermissionsCount());

    return standardPermissions[ index ].permissions;
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
            return i18nc(standardPermissions[ i ].context, standardPermissions[ i ].userString);
        }
    }

    return i18n("Custom Permissions (%1)",
                QString::fromLatin1(KIMAP::Acl::rightsToString(permissions)));
}

QString AclUtils::guessUserName(const QString &loginName, const QString &serverName)
{
    int pos = loginName.indexOf(QLatin1Char('@'));
    if (pos != -1) {
        // strip of the domain part and use user name only
        return loginName.left(pos);
    } else {
        pos = serverName.lastIndexOf(QLatin1Char('.'));
        if (pos == -1) {   // no qualified domain name, only hostname
            return QStringLiteral("%1@%2").arg(loginName, serverName);
        }

        pos = serverName.lastIndexOf(QLatin1Char('.'), pos - 1);
        if (pos == -1) {   // a simple domain name e.g. mydomain.org
            return QStringLiteral("%1@%2").arg(loginName, serverName);
        } else {
            return QStringLiteral("%1@%2").arg(loginName, serverName.mid(pos + 1));
        }
    }
}
