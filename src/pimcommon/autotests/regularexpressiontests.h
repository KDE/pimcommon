/*
  SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef REGULAREXPRESSIONTESTS_H
#define REGULAREXPRESSIONTESTS_H

#include <QObject>

class RegularExpressionTests : public QObject
{
    Q_OBJECT
public:
    explicit RegularExpressionTests(QObject *parent = nullptr);
    ~RegularExpressionTests();
private Q_SLOTS:
    void shouldVerifyQStringListFilterConversion_data();
    void shouldVerifyQStringListFilterConversion();

    void shouldVerifyQStringListFilterTwoConversion_data();
    void shouldVerifyQStringListFilterTwoConversion();

    void shouldVerifyQStringListFilterSpaceConversion();
    void shouldVerifyQStringListFilterSpaceConversion_data();

    void shouldVerifyQStringListFilterDoublePointConversion();
    void shouldVerifyQStringListFilterDoublePointConversion_data();

    void shouldVerifyQStringListFilterWithSharpConversion();
    void shouldVerifyQStringListFilterWithSharpConversion_data();

    void shouldReplaceString_data();
    void shouldReplaceString();

    void shouldRemoveString_data();
    void shouldRemoveString();

    void shouldVerifyQStringListFilterWithStartCharAndEndConversion_data();
    void shouldVerifyQStringListFilterWithStartCharAndEndConversion();

    void shouldVerifyQStringListFilterWithPmailSettingsConversion();
    void shouldVerifyQStringListFilterWithPmailSettingsConversion_data();

    void shouldContainsString_data();
    void shouldContainsString();

    void shouldCaptureValue_data();
    void shouldCaptureValue();
};

#endif // REGULAREXPRESSIONTESTS_H
