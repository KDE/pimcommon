/*
  Copyright (C) 2017-2020 Laurent Montel <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License, version 2, as
  published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef LOGACTIVITIESMANAGERTEST_H
#define LOGACTIVITIESMANAGERTEST_H

#include <QObject>

class LogActivitiesManagerTest : public QObject
{
    Q_OBJECT
public:
    explicit LogActivitiesManagerTest(QObject *parent = nullptr);
    ~LogActivitiesManagerTest();

private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldAppendLog();
    void shouldEnableActivities();
    void shouldClearLog();
};

#endif // LOGACTIVITIESMANAGERTEST_H
