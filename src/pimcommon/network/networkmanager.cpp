/*
  SPDX-FileCopyrightText: 2016-2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "networkmanager.h"
#include <QNetworkConfigurationManager>
using namespace PimCommon;

Q_GLOBAL_STATIC(NetworkManager, s_pNetworkManagerSelf)

NetworkManager::NetworkManager(QObject *parent)
    : QObject(parent)
    , mNetworkConfigureManager(new QNetworkConfigurationManager())
{
}

NetworkManager::~NetworkManager()
{
    delete mNetworkConfigureManager;
}

NetworkManager *NetworkManager::self()
{
    return s_pNetworkManagerSelf();
}

QNetworkConfigurationManager *NetworkManager::networkConfigureManager() const
{
    return mNetworkConfigureManager;
}
