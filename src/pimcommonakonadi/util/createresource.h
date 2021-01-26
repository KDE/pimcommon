/*
  SPDX-FileCopyrightText: 2012-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef PIMCOMMONCREATERESOURCE_H
#define PIMCOMMONCREATERESOURCE_H

#include "pimcommonakonadi_export.h"
#include <QMap>
#include <QObject>
#include <QVariant>

namespace PimCommon
{
/**
 * @brief The CreateResource class
 * @author Laurent Montel <montel@kde.org>
 */
class PIMCOMMONAKONADI_EXPORT CreateResource : public QObject
{
    Q_OBJECT
public:
    explicit CreateResource(QObject *parent = nullptr);
    ~CreateResource();

    Q_REQUIRED_RESULT QString createResource(const QString &resources,
                                             const QString &name,
                                             const QMap<QString, QVariant> &settings,
                                             bool synchronizeTree = false);

Q_SIGNALS:
    void createResourceInfo(const QString &);
    void createResourceError(const QString &);
};
}

#endif // CREATERESOURCE_H
