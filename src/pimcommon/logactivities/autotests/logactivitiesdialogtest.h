/*
  SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef LOGACTIVITIESDIALOGTEST_H
#define LOGACTIVITIESDIALOGTEST_H

#include <QObject>

class LogActivitiesDialogTest : public QObject
{
    Q_OBJECT
public:
    explicit LogActivitiesDialogTest(QObject *parent = nullptr);
    ~LogActivitiesDialogTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldClearLog();
    void shouldHaveCorrectLogActivities();
};

#endif // LOGACTIVITIESDIALOGTEST_H
