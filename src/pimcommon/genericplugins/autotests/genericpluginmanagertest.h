/*
  SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#ifndef GENERICPLUGINMANAGERTEST_H
#define GENERICPLUGINMANAGERTEST_H

#include <QObject>

class GenericPluginManagerTest : public QObject
{
    Q_OBJECT
public:
    explicit GenericPluginManagerTest(QObject *parent = nullptr);
    ~GenericPluginManagerTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldInitialized();
};

#endif // GENERICPLUGINMANAGERTEST_H
