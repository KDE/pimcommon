/*
  SPDX-FileCopyrightText: 2009 Kevin Ottens <ervin@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

// THIS file should not exist and is only a copy of
// kdepim-runtime/resources/shared/singlefileresource

// Any improvements should be done at kdepim-runtime and
// than afterwards copy the new version

#pragma once

#include "pimcommonakonadi_export.h"

#include <Akonadi/Attribute>

#include <KIMAP/Acl>

#include <QMap>

#include <memory>
namespace PimCommon
{
class ImapAclAttributePrivate;
/*!
 * \class PimCommon::ImapAclAttribute
 * \brief The ImapAclAttribute class stores IMAP ACL information as an Akonadi attribute
 * \inmodule PimCommonAkonadi
 * \inheaderfile PimCommonAkonadi/ImapAclAttribute
 * \author Kevin Ottens <ervin@kde.org>
 */
class PIMCOMMONAKONADI_EXPORT ImapAclAttribute : public Akonadi::Attribute
{
public:
    /*!
     * Constructs a default ImapAclAttribute.
     */
    ImapAclAttribute();
    /*!
     * Constructs an ImapAclAttribute with given rights.
     * @param rights The current ACL rights
     * @param oldRights The previous ACL rights
     */
    ImapAclAttribute(const QMap<QByteArray, KIMAP::Acl::Rights> &rights, const QMap<QByteArray, KIMAP::Acl::Rights> &oldRights);
    /*!
     * Destructs the ImapAclAttribute.
     */
    ~ImapAclAttribute() override;
    /*!
     * Sets the ACL rights.
     * @param rights The ACL rights map
     */
    void setRights(const QMap<QByteArray, KIMAP::Acl::Rights> &rights);
    /*!
     * Returns the current ACL rights.
     * @return The ACL rights map
     */
    [[nodiscard]] QMap<QByteArray, KIMAP::Acl::Rights> rights() const;
    /*!
     * Returns the previous ACL rights.
     * @return The old ACL rights map
     */
    [[nodiscard]] QMap<QByteArray, KIMAP::Acl::Rights> oldRights() const;
    /*!
     * Sets the user's own ACL rights.
     * @param rights The user's ACL rights
     */
    void setMyRights(KIMAP::Acl::Rights rights);
    /*!
     * Returns the user's own ACL rights.
     * @return The user's ACL rights
     */
    [[nodiscard]] KIMAP::Acl::Rights myRights() const;
    /*!
     * Returns the type of this attribute.
     * @return The attribute type name
     */
    [[nodiscard]] QByteArray type() const override;
    /*!
     * Creates a clone of this attribute.
     * @return A new ImapAclAttribute with the same data
     */
    ImapAclAttribute *clone() const override;
    /*!
     * Serializes this attribute to a byte array.
     * @return The serialized attribute data
     */
    [[nodiscard]] QByteArray serialized() const override;
    /*!
     * Deserializes an attribute from a byte array.
     * @param data The serialized attribute data
     */
    void deserialize(const QByteArray &data) override;

    /*!
     * Compares this attribute with another for equality.
     * @param other The attribute to compare with
     * @return true if equal, false otherwise
     */
    bool operator==(const ImapAclAttribute &other) const;

private:
    std::unique_ptr<ImapAclAttributePrivate> const d;
};
}
