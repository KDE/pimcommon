/*
  SPDX-FileCopyrightText: 2016-2024 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class ConfigurePluginsListWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit ConfigurePluginsListWidgetTest(QObject *parent = nullptr);
    ~ConfigurePluginsListWidgetTest() override;
private Q_SLOTS:
    void shouldHaveDefaultValue();
};
