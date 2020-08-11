/*
  SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#ifndef LOGACTIVITIESWIDGETTEST_H
#define LOGACTIVITIESWIDGETTEST_H

#include <QObject>

class LogActivitiesWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit LogActivitiesWidgetTest(QObject *parent = nullptr);
    ~LogActivitiesWidgetTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif // LOGACTIVITIESWIDGETTEST_H
