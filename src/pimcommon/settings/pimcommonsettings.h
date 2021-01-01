/*
  SPDX-FileCopyrightText: 2013-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef PIMCOMMON_SETTINGS_H
#define PIMCOMMON_SETTINGS_H

#include "pimcommon_export.h"
#include "pimcommonsetting_base.h"

class QTimer;

namespace PimCommon {
/**
 * @brief The PimCommonSettings class
 * @author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT PimCommonSettings : public PimCommon::PimCommonSettingsBase
{
    Q_OBJECT
public:
    static PimCommonSettings *self();

    /** Call this slot instead of directly @ref KConfig::sync() to
      minimize the overall config writes. Calling this slot will
      schedule a sync of the application config file using a timer, so
      that many consecutive calls can be condensed into a single
      sync, which is more efficient. */
    void requestSync();

private Q_SLOTS:
    void slotSyncNow();

private:
    PimCommonSettings();
    ~PimCommonSettings() override;
    static PimCommonSettings *mSelf;

    QTimer *mConfigSyncTimer = nullptr;
};
}

#endif /* PIMCOMMON_SETTINGS_H */
