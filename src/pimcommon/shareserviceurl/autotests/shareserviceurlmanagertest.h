/*
  SPDX-FileCopyrightText: 2015-2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class ShareServiceUrlManagerTest : public QObject
{
    Q_OBJECT
public:
    explicit ShareServiceUrlManagerTest(QObject *parent = nullptr);
    ~ShareServiceUrlManagerTest() override;

private Q_SLOTS:
    void shouldHaveDefaultValue();

    void shouldGenerateServiceUrl_data();
    void shouldGenerateServiceUrl();
};
