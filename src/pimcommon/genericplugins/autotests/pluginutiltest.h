/*
  SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef PluginUtilTest_H
#define PluginUtilTest_H

#include <QObject>

class PluginUtilTest : public QObject
{
    Q_OBJECT
public:
    explicit PluginUtilTest(QObject *parent = nullptr);
    ~PluginUtilTest();
private Q_SLOTS:
    void shouldTestIsEnabled_data();
    void shouldTestIsEnabled();
};

#endif // PluginUtilTest_H
