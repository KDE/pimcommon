/*
  SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class LogActivitiesDialogTest : public QObject
{
    Q_OBJECT
public:
    explicit LogActivitiesDialogTest(QObject *parent = nullptr);
    ~LogActivitiesDialogTest() override;
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldClearLog();
    void shouldHaveCorrectLogActivities();
};

