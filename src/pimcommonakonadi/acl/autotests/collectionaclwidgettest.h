/*
  SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#ifndef COLLECTIONACLWIDGETTEST_H
#define COLLECTIONACLWIDGETTEST_H

#include <QObject>

class CollectionAclWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit CollectionAclWidgetTest(QObject *parent = nullptr);
    ~CollectionAclWidgetTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif // COLLECTIONACLWIDGETTEST_H
