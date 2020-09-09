/*
  SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef ACTIONTYPETEST_H
#define ACTIONTYPETEST_H

#include <QObject>

class ActionTypeTest : public QObject
{
    Q_OBJECT
public:
    explicit ActionTypeTest(QObject *parent = nullptr);
    ~ActionTypeTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldAssignValue();
};

#endif // ACTIONTYPETEST_H
