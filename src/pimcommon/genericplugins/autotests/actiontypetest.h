/*
  SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class ActionTypeTest : public QObject
{
    Q_OBJECT
public:
    explicit ActionTypeTest(QObject *parent = nullptr);
    ~ActionTypeTest() override;
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldAssignValue();
};

