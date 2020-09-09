/*
  SPDX-FileCopyrightText: 2014-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef RICHTEXTEDITWITHAUTOCORRECTIONTEST_H
#define RICHTEXTEDITWITHAUTOCORRECTIONTEST_H
#include <QObject>

class RichTextEditWithAutoCorrectionTest : public QObject
{
    Q_OBJECT
public:
    RichTextEditWithAutoCorrectionTest();
private Q_SLOTS:
    void shouldNotAutocorrectWhenDisabled();
    void shouldReplaceWordWhenExactText();
    void shouldNotReplaceWordWhenInexactText();
    void shouldReplaceWhenPressEnter();
    void shouldReplaceWhenPressReturn();
};

#endif // RICHTEXTEDITWITHAUTOCORRECTIONTEST_H
