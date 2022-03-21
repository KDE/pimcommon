/*
  SPDX-FileCopyrightText: 2015-2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class GenericPluginManagerTest : public QObject
{
    Q_OBJECT
public:
    explicit GenericPluginManagerTest(QObject *parent = nullptr);
    ~GenericPluginManagerTest() override;
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldInitialized();
};
