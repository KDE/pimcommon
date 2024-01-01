/*
  SPDX-FileCopyrightText: 2014-2024 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#pragma once

#include <QObject>

class ContentTypeWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit ContentTypeWidgetTest(QObject *parent = nullptr);
    ~ContentTypeWidgetTest() override;
private Q_SLOTS:
    void shouldHaveDefaultValue();
};
