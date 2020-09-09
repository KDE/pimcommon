/*
  SPDX-FileCopyrightText: 2014-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef COLLECTIONANNOTATIONSATTRIBUTETEST_H
#define COLLECTIONANNOTATIONSATTRIBUTETEST_H

#include <QObject>

class CollectionAnnotationsAttributeTest : public QObject
{
    Q_OBJECT
public:
    explicit CollectionAnnotationsAttributeTest(QObject *parent = nullptr);
    ~CollectionAnnotationsAttributeTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldAssignAttribute();
    void shouldDeserializedAttribute();
    void shouldCloneAttribute();
    void shouldHaveType();
};

#endif // COLLECTIONANNOTATIONSATTRIBUTETEST_H
