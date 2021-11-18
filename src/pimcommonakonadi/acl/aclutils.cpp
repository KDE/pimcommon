/*
 * SPDX-FileCopyrightText: 2010 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
 * SPDX-FileCopyrightText: 2010 Tobias Koenig <tokoe@kdab.com>
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "aclutils_p.h"

#include <ki18n_version.h>
#if KI18N_VERSION >= QT_VERSION_CHECK(5, 89, 0)
#include <KLazyLocalizedString>
#undef I18NC_NOOP
#define I18NC_NOOP kli18nc
#endif
#include <KLocalizedString>

using namespace PimCommon;

static const struct {
    KIMAP::Acl::Rights permissions;
#if KI18N_VERSION >= QT_VERSION_CHECK(5, 89, 0)
    const KLazyLocalizedString userString;
#else
    const char *context;
    const char *userString;
#endif
} standardPermissions[] = {
    {KIMAP::Acl::None, I18NC_NOOP("Permissions", "None")},

    {KIMAP::Acl::Lookup | KIMAP::Acl::Read | KIMAP::Acl::KeepSeen, I18NC_NOOP("Permissions", "Read")},

    {KIMAP::Acl::Lookup | KIMAP::Acl::Read | KIMAP::Acl::KeepSeen | KIMAP::Acl::Insert | KIMAP::Acl::Post, I18NC_NOOP("Permissions", "Append")},

    {KIMAP::Acl::Lookup | KIMAP::Acl::Read | KIMAP::Acl::KeepSeen | KIMAP::Acl::Insert | KIMAP::Acl::Post | KIMAP::Acl::Write | KIMAP::Acl::CreateMailbox
         | KIMAP::Acl::DeleteMailbox | KIMAP::Acl::DeleteMessage | KIMAP::Acl::Expunge,
     I18NC_NOOP("Permissions", "Write")},

    {KIMAP::Acl::Lookup | KIMAP::Acl::Read | KIMAP::Acl::KeepSeen | KIMAP::Acl::Insert | KIMAP::Acl::Post | KIMAP::Acl::Write | KIMAP::Acl::CreateMailbox
         | KIMAP::Acl::DeleteMailbox | KIMAP::Acl::DeleteMessage | KIMAP::Acl::Expunge | KIMAP::Acl::Admin,
     I18NC_NOOP("Permissions", "All")}};

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
#if KI18N_VERSION >= QT_VERSION_CHECK(5, 89, 0)
            return KLocalizedString(standardPermissions[i].userString).toString();
#else
            return i18nc(standardPermissions[i].context, standardPermissions[i].userString);
#endif
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
