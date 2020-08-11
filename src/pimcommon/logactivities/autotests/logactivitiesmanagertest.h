/*
  SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#ifndef LOGACTIVITIESMANAGERTEST_H
#define LOGACTIVITIESMANAGERTEST_H

#include <QObject>

class LogActivitiesManagerTest : public QObject
{
    Q_OBJECT
public:
    explicit LogActivitiesManagerTest(QObject *parent = nullptr);
    ~LogActivitiesManagerTest();

private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldAppendLog();
    void shouldEnableActivities();
    void shouldClearLog();
};

#endif // LOGACTIVITIESMANAGERTEST_H
