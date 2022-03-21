/*
  SPDX-FileCopyrightText: 2014-2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include <QObject>

class TranslatorTest : public QObject
{
    Q_OBJECT
public:
    TranslatorTest();

private Q_SLOTS:
    void shouldHaveDefaultValuesOnCreation();
    void shouldEnableTranslateButtonWhenTextToTranslateIsNotEmpty();
    void shouldDisableTranslateButtonAndClearTextWhenClickOnClearButton();
    void shouldInvertLanguageWhenClickOnInvertButton();
    void shouldHideWidgetWhenPressEscape();
    void shouldEmitTranslatorWasClosedSignalWhenCloseIt();
};
