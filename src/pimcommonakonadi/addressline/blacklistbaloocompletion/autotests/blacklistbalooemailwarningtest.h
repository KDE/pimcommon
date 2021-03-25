/*
  SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#pragma once

#include <QObject>

class BlackListBalooEmailWarningTest : public QObject
{
    Q_OBJECT
public:
    explicit BlackListBalooEmailWarningTest(QObject *parent = nullptr);
    ~BlackListBalooEmailWarningTest();

private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldEmitSaveChanges();
    void shouldEmitNewSearch();
};

