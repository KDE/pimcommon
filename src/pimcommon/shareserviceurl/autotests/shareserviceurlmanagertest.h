/*
  SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef SHARESERVICEURLMANAGERTEST_H
#define SHARESERVICEURLMANAGERTEST_H

#include <QObject>

class ShareServiceUrlManagerTest : public QObject
{
    Q_OBJECT
public:
    explicit ShareServiceUrlManagerTest(QObject *parent = nullptr);
    ~ShareServiceUrlManagerTest();

private Q_SLOTS:
    void shouldHaveDefaultValue();

    void shouldGenerateServiceUrl_data();
    void shouldGenerateServiceUrl();
};

#endif // SHARESERVICEURLMANAGERTEST_H
