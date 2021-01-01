/*
  SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef CONFIGUREPLUGINSLISTWIDGETTEST_H
#define CONFIGUREPLUGINSLISTWIDGETTEST_H

#include <QObject>

class ConfigurePluginsListWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit ConfigurePluginsListWidgetTest(QObject *parent = nullptr);
    ~ConfigurePluginsListWidgetTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif // CONFIGUREPLUGINSLISTWIDGETTEST_H
