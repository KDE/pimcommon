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
   Provides a singleton which broadcasts status messages by emitting
   signals. Interested mainwindows can connect to the statusMsg()
   signal and update statusBars or whatever they use for showing status.
*/
class BroadcastStatusPrivate;
class PIMCOMMON_EXPORT BroadcastStatus : public QObject
{
    Q_OBJECT

public:
    /*!
     */
    ~BroadcastStatus() override;

    /*! Return the instance of the singleton object for this class */
    static BroadcastStatus *instance();

public Q_SLOTS:
    /*!
      Emit an update status bar signal. It's a slot so it can be hooked up
      to other signals.
    */
    void setStatusMsg(const QString &message);

    /*!
      Set a status message that will go away again with the next call of
      reset().
    */
    void setTransientStatusMsg(const QString &msg);

    /*!
      Reset the status message to what ever non-transient message was last
      active or has since been set.
     */
    void reset();

Q_SIGNALS:
    /*! Emitted when setStatusMsg is called. */
    void statusMsg(const QString &);

protected:
    BroadcastStatus();
    std::unique_ptr<BroadcastStatusPrivate> const d;
};
}
