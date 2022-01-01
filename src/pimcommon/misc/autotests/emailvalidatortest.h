/*
   SPDX-FileCopyrightText: 2017-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class EmailValidatorTest : public QObject
{
    Q_OBJECT
public:
    explicit EmailValidatorTest(QObject *parent = nullptr);
    ~EmailValidatorTest() override = default;

private Q_SLOTS:
    void shouldValidateEmail_data();
    void shouldValidateEmail();
};

