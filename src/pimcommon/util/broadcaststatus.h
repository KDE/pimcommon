/*
  broadcaststatus.h

  This file is part of libkdepim.

  SPDX-FileCopyrightText: 2000 Don Sanders <sanders@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "pimcommon_export.h"
#include <QObject>
#include <memory>
#undef None

namespace PimCommon
{
/*!
 * \class PimCommon::BroadcastStatus
 * \brief The BroadcastStatus class provides a singleton which broadcasts status messages
 * \inmodule PimCommon
 * \inheaderfile PimCommon/BroadcastStatus
 */
class BroadcastStatusPrivate;
class PIMCOMMON_EXPORT BroadcastStatus : public QObject
{
    Q_OBJECT

public:
    /*!
     * Destructs the BroadcastStatus.
     */
    ~BroadcastStatus() override;

    /*!
     * Returns the singleton instance of BroadcastStatus.
     * @return The singleton instance
     */
    static BroadcastStatus *instance();

public Q_SLOTS:
    /*!
     * Sets a status message to be broadcast.
     * @param message The status message to display
     */
    void setStatusMsg(const QString &message);

    /*!
     * Sets a transient status message that will be reset on the next reset() call.
     * @param msg The transient status message
     */
    void setTransientStatusMsg(const QString &msg);

    /*!
     * Resets the status message to the last non-transient message.
     */
    void reset();

Q_SIGNALS:
    /*!
     * Emitted when a status message is set.
     * @param message The status message
     */
    void statusMsg(const QString &);

protected:
    /*!
     * Protected constructor for the singleton pattern.
     */
    BroadcastStatus();
    std::unique_ptr<BroadcastStatusPrivate> const d;
};
}
