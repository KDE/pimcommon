/*
  SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class LogActivitiesWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit LogActivitiesWidgetTest(QObject *parent = nullptr);
    ~LogActivitiesWidgetTest() override;
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

