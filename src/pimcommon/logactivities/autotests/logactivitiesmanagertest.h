/*
  SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class LogActivitiesManagerTest : public QObject
{
    Q_OBJECT
public:
    explicit LogActivitiesManagerTest(QObject *parent = nullptr);
    ~LogActivitiesManagerTest() override;

private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldAppendLog();
    void shouldEnableActivities();
    void shouldClearLog();
};

