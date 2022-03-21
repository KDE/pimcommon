/*
 * SPDX-FileCopyrightText: 2010 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
 * SPDX-FileCopyrightText: 2010 Tobias Koenig <tokoe@kdab.com>
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

#include <KIMAP/Acl>

namespace PimCommon
{
namespace AclUtils
{
/**
 * Returns the number of standard permissions available.
 */
uint standardPermissionsCount();

/**
 * Returns the standard permissions at the given @p index.
 */
KIMAP::Acl::Rights permissionsForIndex(uint index);

/**
 * Returns the index of the given standard @p permissions.
 *
 * If there are no matching permissions, @c -1 is returned.
 */
int indexForPermissions(KIMAP::Acl::Rights permissions);

/**
 * Returns the i18n'd representation of the given @p permissions.
 */
QString permissionsToUserString(KIMAP::Acl::Rights permissions);

/**
 * We call this method if our first try to get the ACLs for the user fails.
 * That's the case if the ACLs use a different user id than the login name.
 *
 * Examples:
 *   login: testuser                acls: testuser@mydomain.org
 *   login: testuser@mydomain.org   acls: testuser
 */
QString guessUserName(const QString &loginName, const QString &serverName);
}
}
