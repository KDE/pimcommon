/*
  Copyright (c) 2017 Montel Laurent <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License, version 2, as
  published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/


#include "logactivitiesmanager.h"
#include "logactivitiesdialog.h"
#include <QTime>

#include <QtGlobal>

using namespace PimCommon;

Q_GLOBAL_STATIC(LogActivitiesManager, s_pLogActivitiesSelf)

class PimCommon::LogActivitiesManagerPrivate
{
public:
    LogActivitiesManagerPrivate()
        : mDialog{nullptr}
    {

    }
    ~LogActivitiesManagerPrivate()
    {
        delete mDialog;
    }

    QStringList mLog;
    PimCommon::LogActivitiesDialog *mDialog;
};

LogActivitiesManager::LogActivitiesManager(QObject *parent)
    : QObject(parent),
      d(new LogActivitiesManagerPrivate)
{

}

LogActivitiesManager::~LogActivitiesManager()
{
    delete d;
}

LogActivitiesManager *LogActivitiesManager::self()
{
    return s_pLogActivitiesSelf;
}

void LogActivitiesManager::appendLog(const QString &str)
{
    const QString timedLog = QLatin1Char('[') + QTime::currentTime().toString() + QLatin1String("] ") + str;
    d->mLog.append(timedLog);
}

QString LogActivitiesManager::log() const
{
    return d->mLog.join(QLatin1Char('\n'));
}

void LogActivitiesManager::clear()
{
    d->mLog.clear();
}

void LogActivitiesManager::showLogActivitiesDialog()
{
    if (!d->mDialog) {
        d->mDialog = new PimCommon::LogActivitiesDialog();
    }
    d->mDialog->show();
}
