/*
  SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#pragma once

#include <QObject>

class BlackListBalooEmailCompletionWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit BlackListBalooEmailCompletionWidgetTest(QObject *parent = nullptr);
    ~BlackListBalooEmailCompletionWidgetTest();

private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldEnablePushButtonWhenTestSizeSupperiorToTwo();
    void shouldChangeEnableSelectUnSelectButton();
};

