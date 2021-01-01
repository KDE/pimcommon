/*
   SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "emailvalidatortest.h"
#include <PimCommon/EmailValidator>
#include <QTest>

QTEST_MAIN(EmailValidatorTest)
Q_DECLARE_METATYPE(QValidator::State)
EmailValidatorTest::EmailValidatorTest(QObject *parent)
    : QObject(parent)
{
}

void EmailValidatorTest::shouldValidateEmail_data()
{
    QTest::addColumn<QString>("email");
    QTest::addColumn<QValidator::State>("state");
    QTest::newRow("empty") << QString() << QValidator::Intermediate;
    QTest::newRow("email") << QStringLiteral("foo@kde.org") << QValidator::Acceptable;
    QTest::newRow("notanemail") << QStringLiteral("foo") << QValidator::Intermediate;
    QTest::newRow("space") << QStringLiteral("foo ") << QValidator::Invalid;
    QTest::newRow("space1") << QStringLiteral(" foo") << QValidator::Invalid;
    QTest::newRow("email2") << QStringLiteral("<foo@kde.org>") << QValidator::Intermediate;
    QTest::newRow("email3") << QStringLiteral("\"bla\" <foo@kde.org>") << QValidator::Invalid;
}

void EmailValidatorTest::shouldValidateEmail()
{
    QFETCH(QString, email);
    QFETCH(QValidator::State, state);
    PimCommon::EmailValidator val(nullptr);
    int pos;
    QCOMPARE(val.validate(email, pos), state);
}
