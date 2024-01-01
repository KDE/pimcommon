/*
  SPDX-FileCopyrightText: 2015-2024 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#pragma once

#include <QObject>

class BlackListBalooEmailListTest : public QObject
{
    Q_OBJECT
public:
    explicit BlackListBalooEmailListTest(QObject *parent = nullptr);
    ~BlackListBalooEmailListTest() override;
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldFillListEmail();
    void shouldFillListWithAlreadyBlackListedEmail();
    void shouldReturnChangedItems();
    void shouldNotAddDuplicateEmails();
    void shouldExcludeDomain();
    void shouldAvoidSameEmailWithDifferentCase();
    void shouldAvoidSameEmailWithDisplayNameOrNot();
};
