/*
  SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class CustomToolsWidgetNgTest : public QObject
{
    Q_OBJECT
public:
    explicit CustomToolsWidgetNgTest(QObject *parent = nullptr);
    ~CustomToolsWidgetNgTest();

private Q_SLOTS:
    void shouldHaveDefaultValue();
};

