/*
  SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class RegularExpressionTests : public QObject
{
    Q_OBJECT
public:
    explicit RegularExpressionTests(QObject *parent = nullptr);
    ~RegularExpressionTests() override;
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
