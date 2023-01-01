/*
  SPDX-FileCopyrightText: 2014-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "collectionannotationsattributetest.h"
#include "../attributes/collectionannotationsattribute.h"
#include <QTest>
CollectionAnnotationsAttributeTest::CollectionAnnotationsAttributeTest(QObject *parent)
    : QObject(parent)
{
}

CollectionAnnotationsAttributeTest::~CollectionAnnotationsAttributeTest() = default;

void CollectionAnnotationsAttributeTest::shouldHaveDefaultValue()
{
    PimCommon::CollectionAnnotationsAttribute attr;
    QVERIFY(attr.annotations().isEmpty());
}

void CollectionAnnotationsAttributeTest::shouldAssignAttribute()
{
    QMap<QByteArray, QByteArray> annotations;
    annotations.insert("foo", "foo");
    annotations.insert("bla", "bla");
    annotations.insert("foo2", "bli");
    PimCommon::CollectionAnnotationsAttribute attr(annotations);
    QCOMPARE(attr.annotations(), annotations);
}

void CollectionAnnotationsAttributeTest::shouldDeserializedAttribute()
{
    QMap<QByteArray, QByteArray> annotations;
    annotations.insert("foo", "foo");
    annotations.insert("bla", "bla");
    annotations.insert("foo2", "bli");
    PimCommon::CollectionAnnotationsAttribute attr(annotations);
    const QByteArray ba = attr.serialized();
    PimCommon::CollectionAnnotationsAttribute result;
    result.deserialize(ba);
    QVERIFY(attr == result);
}

void CollectionAnnotationsAttributeTest::shouldCloneAttribute()
{
    QMap<QByteArray, QByteArray> annotations;
    annotations.insert("foo", "foo");
    annotations.insert("bla", "bla");
    annotations.insert("foo2", "bli");
    PimCommon::CollectionAnnotationsAttribute attr(annotations);
    PimCommon::CollectionAnnotationsAttribute *result = attr.clone();
    QVERIFY(attr == *result);
    delete result;
}

void CollectionAnnotationsAttributeTest::shouldHaveType()
{
    PimCommon::CollectionAnnotationsAttribute attr;
    QCOMPARE(attr.type(), QByteArray("collectionannotations"));
}

QTEST_MAIN(CollectionAnnotationsAttributeTest)
