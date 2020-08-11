/*
  SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#ifndef BLACKLISTBALOOEMAILCOMPLETIONWIDGETTEST_H
#define BLACKLISTBALOOEMAILCOMPLETIONWIDGETTEST_H

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

#endif // BLACKLISTBALOOEMAILCOMPLETIONWIDGETTEST_H
