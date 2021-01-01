/*
   SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef EMAILVALIDATORTEST_H
#define EMAILVALIDATORTEST_H

#include <QObject>

class EmailValidatorTest : public QObject
{
    Q_OBJECT
public:
    explicit EmailValidatorTest(QObject *parent = nullptr);
    ~EmailValidatorTest() = default;

private Q_SLOTS:
    void shouldValidateEmail_data();
    void shouldValidateEmail();
};

#endif // EMAILVALIDATORTEST_H
