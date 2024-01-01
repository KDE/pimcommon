/*
  SPDX-FileCopyrightText: 2015-2024 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class CollectionAclWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit CollectionAclWidgetTest(QObject *parent = nullptr);
    ~CollectionAclWidgetTest() override;
private Q_SLOTS:
    void shouldHaveDefaultValue();
};
