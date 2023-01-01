/*
  SPDX-FileCopyrightText: 2017-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class LineEditWithCompleterNgTest : public QObject
{
    Q_OBJECT
public:
    explicit LineEditWithCompleterNgTest(QObject *parent = nullptr);
    ~LineEditWithCompleterNgTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldAddCompletionItem();
    void shouldClearCompleter();
};
