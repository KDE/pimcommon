/*
  SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#ifndef COMPLETIONCONFIGUREDIALOGTEST_H
#define COMPLETIONCONFIGUREDIALOGTEST_H

#include <QObject>

class CompletionConfigureDialogTest : public QObject
{
    Q_OBJECT
public:
    explicit CompletionConfigureDialogTest(QObject *parent = nullptr);
    ~CompletionConfigureDialogTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void initTestCase();
};

#endif // COMPLETIONCONFIGUREDIALOGTEST_H
