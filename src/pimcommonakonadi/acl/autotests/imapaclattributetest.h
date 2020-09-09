/*
  SPDX-FileCopyrightText: 2014-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#ifndef IMAPACLATTRIBUTETEST_H
#define IMAPACLATTRIBUTETEST_H

#include <QObject>

class ImapAclAttributeTest : public QObject
{
    Q_OBJECT
public:
    explicit ImapAclAttributeTest(QObject *parent = nullptr);
    ~ImapAclAttributeTest();
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

#endif // IMAPACLATTRIBUTETEST_H
