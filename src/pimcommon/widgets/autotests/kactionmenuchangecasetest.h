/*
  SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#ifndef KACTIONMENUCHANGECASETEST_H
#define KACTIONMENUCHANGECASETEST_H

#include <QObject>

class KActionMenuChangeCaseTest : public QObject
{
    Q_OBJECT
public:
    explicit KActionMenuChangeCaseTest(QObject *parent = nullptr);
    ~KActionMenuChangeCaseTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldEmitSignals();
};

#endif // KACTIONMENUCHANGECASETEST_H
