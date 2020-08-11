/*
  SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#ifndef BLACKLISTBALOOEMAILSEARCHJOBTEST_H
#define BLACKLISTBALOOEMAILSEARCHJOBTEST_H

#include <QObject>

class BlackListBalooEmailSearchJobTest : public QObject
{
    Q_OBJECT
public:
    explicit BlackListBalooEmailSearchJobTest(QObject *parent = nullptr);
    ~BlackListBalooEmailSearchJobTest();

private Q_SLOTS:
    void shouldNotSearchWhenTextIsEmpty();
};

#endif // BLACKLISTBALOOEMAILSEARCHJOBTEST_H
