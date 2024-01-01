/*
  SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class NeedUpdateVersionUtilsTest : public QObject
{
    Q_OBJECT
public:
    explicit NeedUpdateVersionUtilsTest(QObject *parent = nullptr);
    ~NeedUpdateVersionUtilsTest() override = default;
private Q_SLOTS:
    void shouldReturnObsoleteVersionStatus();
    void shouldReturnObsoleteVersionStatus_data();
};
