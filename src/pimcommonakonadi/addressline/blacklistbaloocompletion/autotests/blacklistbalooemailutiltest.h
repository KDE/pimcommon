/*
  SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#pragma once

#include <QObject>

class BlackListBalooEmailUtilTest : public QObject
{
    Q_OBJECT
public:
    explicit BlackListBalooEmailUtilTest(QObject *parent = nullptr);
    ~BlackListBalooEmailUtilTest() override;
private Q_SLOTS:
    void shouldReturnEmptyResult();
    void shouldDontChangeWhenNotChanged();
    void shouldCreateNewList();
    void shouldAddNewElements();
};
