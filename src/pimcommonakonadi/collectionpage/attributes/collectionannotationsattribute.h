/*
  SPDX-FileCopyrightText: 2008 Omat Holding B.V. <info@omat.nl>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "pimcommonakonadi_export.h"
#include <Akonadi/Attribute>

#include <QMap>

namespace PimCommon
{
/**
 * @brief The CollectionAnnotationsAttribute class
 */
class PIMCOMMONAKONADI_EXPORT CollectionAnnotationsAttribute : public Akonadi::Attribute
{
public:
    CollectionAnnotationsAttribute();
    explicit CollectionAnnotationsAttribute(const QMap<QByteArray, QByteArray> &annotations);
    ~CollectionAnnotationsAttribute() override = default;

    void setAnnotations(const QMap<QByteArray, QByteArray> &annotations);
    QMap<QByteArray, QByteArray> annotations() const;

    QByteArray type() const override;
    CollectionAnnotationsAttribute *clone() const override;
    QByteArray serialized() const override;
    void deserialize(const QByteArray &data) override;

    bool operator==(const CollectionAnnotationsAttribute &other) const;

private:
    QMap<QByteArray, QByteArray> mAnnotations;
};
}

