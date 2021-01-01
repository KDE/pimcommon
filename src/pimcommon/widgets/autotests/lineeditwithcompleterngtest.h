/*
  SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef LINEEDITWITHCOMPLETERNGTEST_H
#define LINEEDITWITHCOMPLETERNGTEST_H

#include <QObject>

class LineEditWithCompleterNgTest : public QObject
{
    Q_OBJECT
public:
    explicit LineEditWithCompleterNgTest(QObject *parent = nullptr);
    ~LineEditWithCompleterNgTest() = default;

private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldAddCompletionItem();
    void shouldClearCompleter();
};

#endif // LINEEDITWITHCOMPLETERNGTEST_H
