/*
  SPDX-FileCopyrightText: 2013-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "pimcommonsettings.h"
#include <QTimer>

using namespace PimCommon;

PimCommonSettings *PimCommonSettings::mSelf = nullptr;

PimCommonSettings *PimCommonSettings::self()
{
    if (!mSelf) {
        mSelf = new PimCommonSettings();
        mSelf->load();
    }

    return mSelf;
}

PimCommonSettings::PimCommonSettings()
{
    mConfigSyncTimer = new QTimer(this);
    mConfigSyncTimer->setSingleShot(true);
    connect(mConfigSyncTimer, &QTimer::timeout, this, &PimCommonSettings::slotSyncNow);
}

void PimCommonSettings::requestSync()
{
    if (!mConfigSyncTimer->isActive()) {
        mConfigSyncTimer->start(0);
    }
}

void PimCommonSettings::slotSyncNow()
{
    config()->sync();
}

PimCommonSettings::~PimCommonSettings()
{
}
