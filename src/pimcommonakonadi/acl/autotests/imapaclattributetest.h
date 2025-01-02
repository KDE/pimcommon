/*
  SPDX-FileCopyrightText: 2014-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class ImapAclAttributeTest : public QObject
{
    Q_OBJECT
public:
    explicit ImapAclAttributeTest(QObject *parent = nullptr);
    ~ImapAclAttributeTest() override;
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldBuildAttribute();
    void shouldAssignValue();
    void shouldCloneAttr();
    void shouldSerializedAttribute();
    void shouldHaveType();
    void testMyRights();
    void testDeserialize_data();
    void testDeserialize();
    void testSerializeDeserialize_data();
    void testSerializeDeserialize();
    void testOldRights();
};
