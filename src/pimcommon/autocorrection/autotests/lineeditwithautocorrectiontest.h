/*
  SPDX-FileCopyrightText: 2014-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#ifndef LINEEDITWITHAUTOCORRECTIONTEST_H
#define LINEEDITWITHAUTOCORRECTIONTEST_H

#include <QObject>

class LineEditWithAutocorrectionTest : public QObject
{
    Q_OBJECT
public:
    LineEditWithAutocorrectionTest();

private Q_SLOTS:
    void shouldNotAutocorrectWhenDisabled();
    void shouldReplaceWordWhenExactText();
    void shouldNotReplaceWordWhenInexactText();
    void shouldNotAddTwoSpace();
};

#endif // LINEEDITWITHAUTOCORRECTIONTEST_H
