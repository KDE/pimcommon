/*
  SPDX-FileCopyrightText: 2009 Kevin Ottens <ervin@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

// THIS file should not exist and is only a copy of
// kdepim-runtime/resources/shared/singlefileresource

// Any improvements should be done at kdepim-runtime and
// than afterwards copy the new version

#include "imapaclattribute.h"

#include <QByteArray>
#include <QList>

using namespace PimCommon;

class PimCommon::ImapAclAttributePrivate
{
public:
    ImapAclAttributePrivate() = default;

    QMap<QByteArray, KIMAP::Acl::Rights> mRights;
    QMap<QByteArray, KIMAP::Acl::Rights> mOldRights;
    KIMAP::Acl::Rights mMyRights;
};

ImapAclAttribute::ImapAclAttribute()
    : d(new PimCommon::ImapAclAttributePrivate)
{
}

ImapAclAttribute::ImapAclAttribute(const QMap<QByteArray, KIMAP::Acl::Rights> &rights, const QMap<QByteArray, KIMAP::Acl::Rights> &oldRights)
    : d(new PimCommon::ImapAclAttributePrivate)
{
    d->mRights = rights;
    d->mOldRights = oldRights;
}

ImapAclAttribute::~ImapAclAttribute() = default;

void ImapAclAttribute::setRights(const QMap<QByteArray, KIMAP::Acl::Rights> &rights)
{
    d->mOldRights = d->mRights;
    d->mRights = rights;
}

QMap<QByteArray, KIMAP::Acl::Rights> ImapAclAttribute::rights() const
{
    return d->mRights;
}

QMap<QByteArray, KIMAP::Acl::Rights> ImapAclAttribute::oldRights() const
{
    return d->mOldRights;
}

void ImapAclAttribute::setMyRights(KIMAP::Acl::Rights rights)
{
    d->mMyRights = rights;
}

KIMAP::Acl::Rights ImapAclAttribute::myRights() const
{
    return d->mMyRights;
}

QByteArray ImapAclAttribute::type() const
{
    static const QByteArray sType("imapacl");
    return sType;
}

ImapAclAttribute *ImapAclAttribute::clone() const
{
    auto attr = new ImapAclAttribute(d->mRights, d->mOldRights);
    attr->setMyRights(d->mMyRights);
    return attr;
}

QByteArray ImapAclAttribute::serialized() const
{
    QByteArray result;

    bool added = false;
    for (auto it = d->mRights.cbegin(), end = d->mRights.cend(); it != end; ++it) {
        result += it.key();
        result += ' ';
        result += KIMAP::Acl::rightsToString(it.value());
        result += " % "; // We use this separator as '%' is not allowed in keys or values
        added = true;
    }

    if (added) {
        result.chop(3);
    }

    result += " %% ";

    added = false;
    for (auto it = d->mOldRights.cbegin(), end = d->mOldRights.cend(); it != end; ++it) {
        result += it.key();
        result += ' ';
        result += KIMAP::Acl::rightsToString(it.value());
        result += " % "; // We use this separator as '%' is not allowed in keys or values
        added = true;
    }

    if (added) {
        result.chop(3);
    }

    if (d->mMyRights) {
        result += " %% ";
        result += KIMAP::Acl::rightsToString(d->mMyRights);
    }

    return result;
}

static void fillRightsMap(const QList<QByteArray> &rights, QMap<QByteArray, KIMAP::Acl::Rights> &map)
{
    for (const QByteArray &right : rights) {
        const QByteArray trimmed = right.trimmed();
        const int wsIndex = trimmed.indexOf(' ');
        const QByteArray id = trimmed.mid(0, wsIndex).trimmed();
        if (!id.isEmpty()) {
            const bool noValue = (wsIndex == -1);
            if (noValue) {
                map[id] = KIMAP::Acl::None;
            } else {
                const QByteArray value = trimmed.mid(wsIndex + 1, right.length() - wsIndex).trimmed();
                map[id] = KIMAP::Acl::rightsFromString(value);
            }
        }
    }
}

void ImapAclAttribute::deserialize(const QByteArray &data)
{
    d->mRights.clear();
    d->mOldRights.clear();
    d->mMyRights = KIMAP::Acl::None;

    QList<QByteArray> parts;
    int lastPos = 0;
    int pos;
    while ((pos = data.indexOf(" %% ", lastPos)) != -1) {
        parts << data.mid(lastPos, pos - lastPos);
        lastPos = pos + 4;
    }
    parts << data.mid(lastPos);

    if (parts.size() < 2) {
        return;
    }
    fillRightsMap(parts.at(0).split('%'), d->mRights);
    fillRightsMap(parts.at(1).split('%'), d->mOldRights);
    if (parts.size() >= 3) {
        d->mMyRights = KIMAP::Acl::rightsFromString(parts.at(2));
    }
}

bool ImapAclAttribute::operator==(const ImapAclAttribute &other) const
{
    return (oldRights() == other.oldRights()) && (rights() == other.rights()) && (myRights() == other.myRights());
}
