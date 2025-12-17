/*
  SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#pragma once

#include <QObject>

class BlackListBalooEmailCompletionWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit BlackListBalooEmailCompletionWidgetTest(QObject *parent = nullptr);
    ~BlackListBalooEmailCompletionWidgetTest() override;

private Q_SLOTS:
    void shouldHaveDefaultValue();
};
