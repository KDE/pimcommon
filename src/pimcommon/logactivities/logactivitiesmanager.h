/*
  SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef LOGACTIVITIESMANAGER_H
#define LOGACTIVITIESMANAGER_H

#include "pimcommon_export.h"
#include <QObject>
namespace PimCommon
{
class LogActivitiesManagerPrivate;
/**
 * @brief The LogActivitiesManager class
 * @author Laurent Montel <montel@kde.org>
 */
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
