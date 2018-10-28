/*
  Copyright (C) 2017-2018 Montel Laurent <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef LOGACTIVITIESMANAGER_H
#define LOGACTIVITIESMANAGER_H

#include <QObject>
#include "pimcommon_export.h"
namespace PimCommon {
class LogActivitiesManagerPrivate;
class PIMCOMMON_EXPORT LogActivitiesManager : public QObject
{
    Q_OBJECT
public:
    explicit LogActivitiesManager(QObject *parent = nullptr);
    ~LogActivitiesManager();

    static LogActivitiesManager *self();

    void appendLog(const QString &str);

    Q_REQUIRED_RESULT QString log() const;

    void clear();

    void showLogActivitiesDialog();

    void setEnableLogActivities(bool b);
    bool enableLogActivities() const;

Q_SIGNALS:
    void logEntryAdded(const QString &entry);
    void logEntryCleared();

private:
    LogActivitiesManagerPrivate *const d;
};
}
#endif // LOGACTIVITIESMANAGER_H
