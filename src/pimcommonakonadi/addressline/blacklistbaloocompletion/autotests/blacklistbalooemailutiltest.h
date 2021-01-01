/*
  SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#ifndef BLACKLISTBALOOEMAILUTILTEST_H
#define BLACKLISTBALOOEMAILUTILTEST_H

#include <QObject>

class BlackListBalooEmailUtilTest : public QObject
{
    Q_OBJECT
public:
    explicit BlackListBalooEmailUtilTest(QObject *parent = nullptr);
    ~BlackListBalooEmailUtilTest();
private Q_SLOTS:
    void shouldReturnEmptyResult();
    void shouldDontChangeWhenNotChanged();
    void shouldCreateNewList();
    void shouldAddNewElements();
};

#endif // BLACKLISTBALOOEMAILUTILTEST_H
