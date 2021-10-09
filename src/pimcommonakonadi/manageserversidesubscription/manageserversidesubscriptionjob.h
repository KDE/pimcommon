/*
  SPDX-FileCopyrightText: 2014-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "pimcommonakonadi_export.h"
#include <Akonadi/Collection>
#include <QObject>
#include <QSharedPointer>
class QDBusPendingCallWatcher;
namespace PimCommon
{
class ManageServerSideSubscriptionJobPrivate;
/**
 * @brief The ManageServerSideSubscriptionJob class
 * @author Laurent Montel <montel@kde.org>
 */
class PIMCOMMONAKONADI_EXPORT ManageServerSideSubscriptionJob : public QObject
{
    Q_OBJECT
public:
    explicit ManageServerSideSubscriptionJob(QObject *parent = nullptr);

    ~ManageServerSideSubscriptionJob() override;

    void start();
    void setCurrentCollection(const Akonadi::Collection &col);

    void setParentWidget(QWidget *parentWidget);

private:
    void slotConfigureSubscriptionFinished(QDBusPendingCallWatcher *watcher);
    std::unique_ptr<ManageServerSideSubscriptionJobPrivate> const d;
};
}

