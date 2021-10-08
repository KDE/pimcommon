/*
  broadcaststatus.cpp

  This file is part of libkdepim.

  Author: Don Sanders <sanders@kde.org>

  SPDX-FileCopyrightText: 2000 Don Sanders <sanders@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "broadcaststatus.h"
#include <QCoreApplication>

static PimCommon::BroadcastStatus *instance_;

static void deleteGlobalStaticBroadcastStatus()
{
    delete instance_;
    instance_ = nullptr;
}

namespace PimCommon
{
BroadcastStatus *BroadcastStatus::instance()
{
    if (!instance_) {
        instance_ = new BroadcastStatus();
        qAddPostRoutine(deleteGlobalStaticBroadcastStatus);
    }
    return instance_;
}

class BroadcastStatusPrivate
{
public:
    BroadcastStatusPrivate()
    {
    }

    QString mStatusMsg;
    bool mTransientActive = false;
};

BroadcastStatus::BroadcastStatus()
    : d(new PimCommon::BroadcastStatusPrivate)
{
}

BroadcastStatus::~BroadcastStatus()
{
    instance_ = nullptr;
}

void BroadcastStatus::setStatusMsg(const QString &message)
{
    d->mStatusMsg = message;
    if (!d->mTransientActive) {
        Q_EMIT statusMsg(message);
    }
}

void BroadcastStatus::setTransientStatusMsg(const QString &msg)
{
    d->mTransientActive = true;
    Q_EMIT statusMsg(msg);
}

void BroadcastStatus::reset()
{
    d->mTransientActive = false;
    // restore
    Q_EMIT statusMsg(d->mStatusMsg);
}
}
