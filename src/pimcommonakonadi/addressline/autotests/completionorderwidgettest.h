/*
  SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#ifndef COMPLETIONORDERWIDGETTEST_H
#define COMPLETIONORDERWIDGETTEST_H

#include <QObject>

class CompletionOrderWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit CompletionOrderWidgetTest(QObject *parent = nullptr);
    ~CompletionOrderWidgetTest();

private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif // COMPLETIONORDERWIDGETTEST_H
