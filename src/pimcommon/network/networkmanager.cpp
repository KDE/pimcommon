/*
  SPDX-FileCopyrightText: 2016-2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "networkmanager.h"
#include "pimcommon_debug.h"
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
#include <QNetworkInformation>
#else
#include <QNetworkConfigurationManager>
#endif
using namespace PimCommon;

Q_GLOBAL_STATIC(NetworkManager, s_pNetworkManagerSelf)

NetworkManager::NetworkManager(QObject *parent)
    : QObject(parent)
    , mNetworkConfigureManager(new QNetworkConfigurationManager())
{
    connect(mNetworkConfigureManager, &QNetworkConfigurationManager::onlineStateChanged, this, &NetworkManager::networkStatusChanged);
}

NetworkManager::~NetworkManager()
{
    delete mNetworkConfigureManager;
}

NetworkManager *NetworkManager::self()
{
    return s_pNetworkManagerSelf();
}

bool NetworkManager::isOnline() const
{
#if QT_VERSION >= QT_VERSION_CHECK(6, 1, 0)
    if (QNetworkInformation::load(QNetworkInformation::Feature::Reachability)) {
        return QNetworkInformation::instance()->reachability() == QNetworkInformation::Reachability::Online;
    } else {
        qCWarning(PIMCOMMON_LOG) << "Couldn't find a working backend for QNetworkInformation";
        return false;
    }
#else
    return mNetworkConfigureManager->isOnline();
#endif
}
