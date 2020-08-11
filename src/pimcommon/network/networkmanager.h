/*
  SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef NetworkManager_H
#define NetworkManager_H

#include <QObject>
#include "pimcommon_export.h"
class QNetworkConfigurationManager;
namespace PimCommon {
/**
 * @brief The NetworkManager class
 * @author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT NetworkManager : public QObject
{
    Q_OBJECT
public:
    explicit NetworkManager(QObject *parent = nullptr);
    ~NetworkManager();
    static NetworkManager *self();

    Q_REQUIRED_RESULT QNetworkConfigurationManager *networkConfigureManager() const;

private:
    QNetworkConfigurationManager *mNetworkConfigureManager = nullptr;
};
}

#endif // NetworkManager_H
