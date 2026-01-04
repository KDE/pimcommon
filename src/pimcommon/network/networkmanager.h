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
 * \brief The NetworkManager class
 * @author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT NetworkManager : public QObject
{
    Q_OBJECT
public:
    /*!
     */
    explicit NetworkManager(QObject *parent = nullptr);
    /*!
     */
    ~NetworkManager() override;
    /*!
     */
    static NetworkManager *self();

    /*!
     */
    [[nodiscard]] bool isOnline() const;

Q_SIGNALS:
    /*!
     */
    void networkStatusChanged(bool isOnline);

private:
    PIMCOMMON_NO_EXPORT void refreshStatus();

    bool m_isOnline = false;
};
}
