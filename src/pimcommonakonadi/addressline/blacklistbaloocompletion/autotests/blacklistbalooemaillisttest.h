/*
  SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#ifndef BLACKLISTBALOOEMAILLISTTEST_H
#define BLACKLISTBALOOEMAILLISTTEST_H

#include <QObject>

class BlackListBalooEmailListTest : public QObject
{
    Q_OBJECT
public:
    explicit BlackListBalooEmailListTest(QObject *parent = nullptr);
    ~BlackListBalooEmailListTest();
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

#endif // BLACKLISTBALOOEMAILLISTTEST_H
