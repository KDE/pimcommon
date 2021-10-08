/*
  SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "logactivitiesmanager.h"
#include "logactivitiesdialog.h"
#include <QPointer>
#include <QTime>

using namespace PimCommon;

Q_GLOBAL_STATIC(LogActivitiesManager, s_pLogActivitiesSelf)

class PimCommon::LogActivitiesManagerPrivate
{
public:
    LogActivitiesManagerPrivate()
    {
    }

    ~LogActivitiesManagerPrivate()
    {
        // Disable delete it.
        // delete mDialog;
    }

    QStringList mLog;
    QPointer<PimCommon::LogActivitiesDialog> mDialog = nullptr;
    bool mEnableLogActivities = false;
};

LogActivitiesManager::LogActivitiesManager(QObject *parent)
    : QObject(parent)
    , d(new LogActivitiesManagerPrivate)
{
}

LogActivitiesManager::~LogActivitiesManager() = default;

LogActivitiesManager *LogActivitiesManager::self()
{
    return s_pLogActivitiesSelf;
}

void LogActivitiesManager::appendLog(const QString &str)
{
    if (d->mEnableLogActivities) {
        const QString timedLog = QLatin1Char('[') + QTime::currentTime().toString() + QLatin1String("] ") + str;
        d->mLog.append(timedLog);
        Q_EMIT logEntryAdded(timedLog);
    }
}

QString LogActivitiesManager::log() const
{
    return d->mLog.join(QLatin1Char('\n'));
}

void LogActivitiesManager::clear()
{
    d->mLog.clear();
    Q_EMIT logEntryCleared();
}

void LogActivitiesManager::showLogActivitiesDialog()
{
    if (!d->mDialog) {
        d->mDialog = new PimCommon::LogActivitiesDialog();
        d->mDialog->setAttribute(Qt::WA_DeleteOnClose, true);
        connect(d->mDialog.data(), &LogActivitiesDialog::logCleared, this, &LogActivitiesManager::clear);
    }
    d->mDialog->setLog(log());
    d->mDialog->show();
}

void LogActivitiesManager::setEnableLogActivities(bool b)
{
    d->mEnableLogActivities = b;
    if (!d->mEnableLogActivities) {
        clear();
    }
}

bool LogActivitiesManager::enableLogActivities() const
{
    return d->mEnableLogActivities;
}
