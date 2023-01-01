/*
  SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class PluginUtilTest : public QObject
{
    Q_OBJECT
public:
    explicit PluginUtilTest(QObject *parent = nullptr);
    ~PluginUtilTest() override;
private Q_SLOTS:
    void shouldTestIsEnabled_data();
    void shouldTestIsEnabled();
};
