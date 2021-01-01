/*
  SPDX-FileCopyrightText: 2014-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef MANAGESERVERSIDESUBSCRIPTIONJOB_H
#define MANAGESERVERSIDESUBSCRIPTIONJOB_H

#include <QObject>
#include "pimcommonakonadi_export.h"
#include <QSharedPointer>
#include <AkonadiCore/collection.h>
class QDBusPendingCallWatcher;
namespace PimCommon {
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

    ~ManageServerSideSubscriptionJob();

    void start();
    void setCurrentCollection(const Akonadi::Collection &col);

    void setParentWidget(QWidget *parentWidget);

private:
    void slotConfigureSubscriptionFinished(QDBusPendingCallWatcher *watcher);
    ManageServerSideSubscriptionJobPrivate *const d;
};
}

#endif // MANAGESERVERSIDESUBSCRIPTIONJOB_H
