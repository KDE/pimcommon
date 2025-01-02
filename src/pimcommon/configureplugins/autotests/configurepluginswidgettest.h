/*
  SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class ConfigurePluginsWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit ConfigurePluginsWidgetTest(QObject *parent = nullptr);
    ~ConfigurePluginsWidgetTest() override;
private Q_SLOTS:
    void shouldHaveDefaultValue();
};
