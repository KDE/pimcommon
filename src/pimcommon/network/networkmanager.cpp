/*
  SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "networkmanager.h"
#include <QNetworkInformation>
using namespace PimCommon;

Q_GLOBAL_STATIC(NetworkManager, s_pNetworkManagerSelf)

NetworkManager::NetworkManager(QObject *parent)
    : QObject(parent)
{
    QNetworkInformation::instance()->loadBackendByFeatures(QNetworkInformation::Feature::Reachability);
    connect(QNetworkInformation::instance(), &QNetworkInformation::reachabilityChanged, this, &NetworkManager::refreshStatus);
    connect(QNetworkInformation::instance(), &QNetworkInformation::isBehindCaptivePortalChanged, this, &NetworkManager::refreshStatus);
    refreshStatus();
}

NetworkManager::~NetworkManager()
{
}

NetworkManager *NetworkManager::self()
{
    return s_pNetworkManagerSelf();
}

bool NetworkManager::isOnline() const
{
    return m_isOnline;
}

void NetworkManager::refreshStatus()
{
    const auto info = QNetworkInformation::instance();
    const bool newIsOnline = !info || (info->reachability() == QNetworkInformation::Reachability::Online && !info->isBehindCaptivePortal());
    if (newIsOnline != m_isOnline) {
        m_isOnline = newIsOnline;
        Q_EMIT networkStatusChanged(m_isOnline);
    }
}

#include "moc_networkmanager.cpp"
