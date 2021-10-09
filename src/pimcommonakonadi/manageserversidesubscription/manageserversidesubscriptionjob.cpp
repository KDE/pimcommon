/*
  SPDX-FileCopyrightText: 2014-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "manageserversidesubscriptionjob.h"
#include "pimcommonakonadi_debug.h"
#include "util/mailutil.h"

#include <Akonadi/ServerManager>

#include <KLocalizedString>
#include <KMessageBox>

#include <QDBusConnection>
#include <QDBusInterface>
#include <QDBusPendingCall>
#include <QDBusPendingReply>

using namespace PimCommon;

class PimCommon::ManageServerSideSubscriptionJobPrivate
{
public:
    ManageServerSideSubscriptionJobPrivate()
    {
    }

    Akonadi::Collection mCurrentCollection;
    QWidget *mParentWidget = nullptr;
};

ManageServerSideSubscriptionJob::ManageServerSideSubscriptionJob(QObject *parent)
    : QObject(parent)
    , d(new PimCommon::ManageServerSideSubscriptionJobPrivate)
{
}

ManageServerSideSubscriptionJob::~ManageServerSideSubscriptionJob() = default;

void ManageServerSideSubscriptionJob::start()
{
    if (!d->mCurrentCollection.isValid()) {
        qCDebug(PIMCOMMONAKONADI_LOG) << " collection not defined";
        deleteLater();
        return;
    }
    bool isImapOnline = false;
    if (PimCommon::MailUtil::isImapFolder(d->mCurrentCollection, isImapOnline)) {
        const QString service = Akonadi::ServerManager::agentServiceName(Akonadi::ServerManager::Resource, d->mCurrentCollection.resource());
        QDBusInterface iface(service, QStringLiteral("/"), QStringLiteral("org.kde.Akonadi.ImapResourceBase"), QDBusConnection::sessionBus(), this);
        if (!iface.isValid()) {
            qCDebug(PIMCOMMONAKONADI_LOG) << "Cannot create imap dbus interface for service " << service;
            deleteLater();
            return;
        }
        QDBusPendingCall call = iface.asyncCall(QStringLiteral("configureSubscription"), (qlonglong)d->mParentWidget->winId());
        auto watcher = new QDBusPendingCallWatcher(call, this);
        connect(watcher, &QDBusPendingCallWatcher::finished, this, &ManageServerSideSubscriptionJob::slotConfigureSubscriptionFinished);
    }
}

void ManageServerSideSubscriptionJob::slotConfigureSubscriptionFinished(QDBusPendingCallWatcher *watcher)
{
    QDBusPendingReply<int> reply = *watcher;
    if (reply.isValid()) {
        if (reply == -2) {
            KMessageBox::error(
                d->mParentWidget,
                i18n("IMAP server not configured yet. Please configure the server in the IMAP account before setting up server-side subscription."));
        } else if (reply == -1) {
            KMessageBox::error(d->mParentWidget, i18n("Log in failed, please configure the IMAP account before setting up server-side subscription."));
        }
    } else {
        qCDebug(PIMCOMMONAKONADI_LOG) << "ManageServerSideSubscriptionJob return an invalid reply";
    }
    watcher->deleteLater();
    deleteLater();
}

void ManageServerSideSubscriptionJob::setParentWidget(QWidget *parentWidget)
{
    d->mParentWidget = parentWidget;
}

void ManageServerSideSubscriptionJob::setCurrentCollection(const Akonadi::Collection &col)
{
    d->mCurrentCollection = col;
}
