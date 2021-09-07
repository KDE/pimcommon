/*
  SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "imapresourcecapabilitiesmanager.h"
#include "pimcommonakonadi_debug.h"
#include "util/pimutil.h"

#include <Akonadi/AgentManager>
#include <Akonadi/ServerManager>

#include <QDBusConnection>
#include <QDBusInterface>
#include <QDBusPendingCall>
#include <QDBusPendingReply>

using namespace PimCommon;
ImapResourceCapabilitiesManager::ImapResourceCapabilitiesManager(QObject *parent)
    : QObject(parent)
{
    init();
}

ImapResourceCapabilitiesManager::~ImapResourceCapabilitiesManager()
{
}

void ImapResourceCapabilitiesManager::slotInstanceAdded(const Akonadi::AgentInstance &instance)
{
    searchCapabilities(instance.identifier());
}

void ImapResourceCapabilitiesManager::slotInstanceRemoved(const Akonadi::AgentInstance &instance)
{
    mImapResource.remove(instance.identifier());
}

void ImapResourceCapabilitiesManager::searchCapabilities(const QString &identifier)
{
    // By default makes it as true.
    mImapResource.insert(identifier, true);
    const QString service = Akonadi::ServerManager::agentServiceName(Akonadi::ServerManager::Resource, identifier);
    QDBusInterface iface(service, QStringLiteral("/"), QStringLiteral("org.kde.Akonadi.ImapResourceBase"), QDBusConnection::sessionBus(), this);

    if (iface.isValid()) {
        QDBusPendingCall call = iface.asyncCall(QStringLiteral("serverCapabilities"));
        auto watcher = new QDBusPendingCallWatcher(call, this);
        watcher->setProperty("identifier", identifier);
        connect(watcher, &QDBusPendingCallWatcher::finished, this, &ImapResourceCapabilitiesManager::slotCapabilities);
    } else {
        qCDebug(PIMCOMMONAKONADI_LOG) << "interface not valid";
    }
}

void ImapResourceCapabilitiesManager::slotCapabilities(QDBusPendingCallWatcher *watcher)
{
    QDBusPendingReply<QStringList> reply = *watcher;
    if (reply.isValid()) {
        if (watcher->property("identifier").isValid()) {
            const QStringList capabilities = reply.value();
            mImapResource.insert(watcher->property("identifier").toString(), capabilities.contains(QLatin1String("ANNOTATEMORE")));
        }
    }
    watcher->deleteLater();
    watcher = nullptr;
}

void ImapResourceCapabilitiesManager::init()
{
    const Akonadi::AgentInstance::List lstInstances = Akonadi::AgentManager::self()->instances();
    for (const Akonadi::AgentInstance &instance : lstInstances) {
        const QString identifier = instance.identifier();
        if (PimCommon::Util::isImapResource(identifier)) {
            searchCapabilities(identifier);
        }
    }
    connect(Akonadi::AgentManager::self(), &Akonadi::AgentManager::instanceAdded, this, &ImapResourceCapabilitiesManager::slotInstanceAdded);
    connect(Akonadi::AgentManager::self(), &Akonadi::AgentManager::instanceRemoved, this, &ImapResourceCapabilitiesManager::slotInstanceRemoved);
}

bool ImapResourceCapabilitiesManager::hasAnnotationSupport(const QString &identifier) const
{
    if (!PimCommon::Util::isImapResource(identifier)) {
        return false;
    }
    return mImapResource.value(identifier, true);
}
