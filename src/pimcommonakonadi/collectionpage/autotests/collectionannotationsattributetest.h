/*
  SPDX-FileCopyrightText: 2014-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class CollectionAnnotationsAttributeTest : public QObject
{
    Q_OBJECT
public:
    explicit CollectionAnnotationsAttributeTest(QObject *parent = nullptr);
    ~CollectionAnnotationsAttributeTest() override;
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldAssignAttribute();
    void shouldDeserializedAttribute();
    void shouldCloneAttribute();
    void shouldHaveType();
};

