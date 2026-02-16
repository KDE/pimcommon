/*
  SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "pimcommon_export.h"
#include <QObject>
namespace PimCommon
{
/*!
 * \class PimCommon::NetworkManager
 * \brief The NetworkManager class manages network status
 * \inmodule PimCommon
 * \inheaderfile PimCommon/NetworkManager
 * \author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT NetworkManager : public QObject
{
    Q_OBJECT
public:
    /*!
     * Constructs a NetworkManager.
     * @param parent The parent QObject
     */
    explicit NetworkManager(QObject *parent = nullptr);
    /*!
     * Destructs the NetworkManager.
     */
    ~NetworkManager() override;
    /*!
     * Returns the singleton instance of NetworkManager.
     * @return The singleton instance
     */
    static NetworkManager *self();

    /*!
     * Returns whether the network is online.
     * @return true if the network is online, false otherwise
     */
    [[nodiscard]] bool isOnline() const;

Q_SIGNALS:
    /*!
     * Emitted when the network status changes.
     * @param isOnline true if the network is online, false otherwise
     */
    void networkStatusChanged(bool isOnline);

private:
    PIMCOMMON_NO_EXPORT void refreshStatus();

    bool m_isOnline = false;
};
}
