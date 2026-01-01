/*
  SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class KActionMenuChangeCaseTest : public QObject
{
    Q_OBJECT
public:
    explicit KActionMenuChangeCaseTest(QObject *parent = nullptr);
    ~KActionMenuChangeCaseTest() override;
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldEmitSignals();
};
