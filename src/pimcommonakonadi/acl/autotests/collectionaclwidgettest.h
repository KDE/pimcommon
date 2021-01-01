/*
  SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
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
