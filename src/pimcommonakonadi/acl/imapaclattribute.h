/*
  SPDX-FileCopyrightText: 2009 Kevin Ottens <ervin@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

// THIS file should not exist and is only a copy of
// kdepim-runtime/resources/shared/singlefileresource

// Any improvements should be done at kdepim-runtime and
// than afterwards copy the new version

#ifndef PIMCOMMON_IMAPACLATTRIBUTE_H
#define PIMCOMMON_IMAPACLATTRIBUTE_H

#include "pimcommonakonadi_export.h"

#include <Attribute>

#include <KIMAP/Acl>

#include <QMap>

namespace PimCommon {
class ImapAclAttributePrivate;
/**
 * @brief The ImapAclAttribute class
 */
class PIMCOMMONAKONADI_EXPORT ImapAclAttribute : public Akonadi::Attribute
{
public:
    ImapAclAttribute();
    ImapAclAttribute(const QMap<QByteArray, KIMAP::Acl::Rights> &rights, const QMap<QByteArray, KIMAP::Acl::Rights> &oldRights);
    ~ImapAclAttribute() override;
    void setRights(const QMap<QByteArray, KIMAP::Acl::Rights> &rights);
    QMap<QByteArray, KIMAP::Acl::Rights> rights() const;
    QMap<QByteArray, KIMAP::Acl::Rights> oldRights() const;
    void setMyRights(KIMAP::Acl::Rights rights);
    KIMAP::Acl::Rights myRights() const;
    QByteArray type() const override;
    ImapAclAttribute *clone() const override;
    QByteArray serialized() const override;
    void deserialize(const QByteArray &data) override;

    bool operator==(const ImapAclAttribute &other) const;
private:
    ImapAclAttributePrivate *const d;
    QMap<QByteArray, KIMAP::Acl::Rights> mRights;
    QMap<QByteArray, KIMAP::Acl::Rights> mOldRights;
    KIMAP::Acl::Rights mMyRights;
};
}

#endif
