/*
  SPDX-FileCopyrightText: 2012-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "pimcommonakonadi_export.h"
#include <QMap>
#include <QObject>
#include <QVariant>

namespace PimCommon
{
/*!
 * \class CreateResource
 * \brief The CreateResource class creates Akonadi resources
 * \inmodule PimCommonAkonadi
 * \inheaderfile PimCommonAkonadi/CreateResource
 * \author Laurent Montel <montel@kde.org>
 */
class PIMCOMMONAKONADI_EXPORT CreateResource : public QObject
{
    Q_OBJECT
public:
    /*!
     * Constructs a CreateResource.
     * @param parent The parent QObject
     */
    explicit CreateResource(QObject *parent = nullptr);
    /*!
     * Destructs the CreateResource.
     */
    ~CreateResource() override;

    /*!
     * Creates an Akonadi resource with the given settings.
     * @param resources The type of resource to create
     * @param name The name for the resource
     * @param settings The configuration settings for the resource
     * @param synchronizeTree Whether to synchronize the tree after creation
     * @return The identifier of the created resource
     */
    [[nodiscard]] QString createResource(const QString &resources, const QString &name, const QMap<QString, QVariant> &settings, bool synchronizeTree = false);

Q_SIGNALS:
    /*!
     * Emitted when resource creation information is available.
     * @param info The information message
     */
    void createResourceInfo(const QString &);
    /*!
     * Emitted when a resource creation error occurs.
     * @param error The error message
     */
    void createResourceError(const QString &);
};
}
