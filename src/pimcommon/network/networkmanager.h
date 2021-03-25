/*
  SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "pimcommon_export.h"
#include <QObject>
class QNetworkConfigurationManager;
namespace PimCommon
{
/**
 * @brief The NetworkManager class
 * @author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT NetworkManager : public QObject
{
    Q_OBJECT
public:
    explicit NetworkManager(QObject *parent = nullptr);
    ~NetworkManager() override;
    static NetworkManager *self();

    Q_REQUIRED_RESULT QNetworkConfigurationManager *networkConfigureManager() const;

private:
    QNetworkConfigurationManager *const mNetworkConfigureManager;
};
}

