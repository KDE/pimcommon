/*
  Copyright (c) 2014-2018 Montel Laurent <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "manageserversidesubscriptionjob.h"
#include "util/mailutil.h"
#include "pimcommonakonadi_debug.h"

#include <AkonadiCore/ServerManager>

#include <KDBusConnectionPool>
#include <KLocalizedString>
#include <KMessageBox>

#include <QDBusInterface>
#include <QDBusPendingCall>
#include <QDBusPendingReply>

using namespace PimCommon;

class PimCommon::ManageServerSideSubscriptionJobPrivate
{
public:
    ManageServerSideSubscriptionJobPrivate()
        : mParentWidget(nullptr)
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

ManageServerSideSubscriptionJob::~ManageServerSideSubscriptionJob()
{
    delete d;
}

void ManageServerSideSubscriptionJob::start()
{
    if (!d->mCurrentCollection.isValid()) {
        qCDebug(PIMCOMMONAKONADI_LOG) << " collection not defined";
        deleteLater();
        return;
    }
    bool isImapOnline = false;
    if (PimCommon::MailUtil::isImapFolder(d->mCurrentCollection, isImapOnline)) {
        const QString service
            = Akonadi::ServerManager::agentServiceName(Akonadi::ServerManager::Resource,
                                                       d->mCurrentCollection.resource());
        QDBusInterface iface(service,
                             QStringLiteral("/"), QStringLiteral("org.kde.Akonadi.ImapResourceBase"),
                             KDBusConnectionPool::threadConnection(), this);
        if (!iface.isValid()) {
            qCDebug(PIMCOMMONAKONADI_LOG) << "Cannot create imap dbus interface for service " << service;
            deleteLater();
            return;
        }
        QDBusPendingCall call = iface.asyncCall(QStringLiteral("configureSubscription"), (qlonglong)d->mParentWidget->winId());
        QDBusPendingCallWatcher *watcher = new QDBusPendingCallWatcher(call, this);
        connect(watcher, &QDBusPendingCallWatcher::finished, this, &ManageServerSideSubscriptionJob::slotConfigureSubscriptionFinished);
    }
}

void ManageServerSideSubscriptionJob::slotConfigureSubscriptionFinished(QDBusPendingCallWatcher *watcher)
{
    QDBusPendingReply<int> reply = *watcher;
    if (reply.isValid()) {
        if (reply == -2) {
            KMessageBox::error(d->mParentWidget, i18n("IMAP server not configured yet. Please configure the server in the IMAP account before setting up server-side subscription."));
        } else if (reply == -1) {
            KMessageBox::error(d->mParentWidget, i18n("Log in failed, please configure the IMAP account before setting up server-side subscription."));
        }
    } else {
        qCDebug(PIMCOMMONAKONADI_LOG) << "ManageServerSideSubscriptionJob return an invalid reply";
    }
    watcher->deleteLater();
    watcher = nullptr;
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
