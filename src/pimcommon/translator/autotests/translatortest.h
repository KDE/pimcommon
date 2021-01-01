/*
  SPDX-FileCopyrightText: 2014-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef TRANSLATORTEST_H
#define TRANSLATORTEST_H
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

#endif // TRANSLATORTEST_H
