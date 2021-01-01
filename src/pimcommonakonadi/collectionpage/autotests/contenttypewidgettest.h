/*
  SPDX-FileCopyrightText: 2014-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#ifndef CONTENTTYPEWIDGETTEST_H
#define CONTENTTYPEWIDGETTEST_H

#include <QObject>

class ContentTypeWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit ContentTypeWidgetTest(QObject *parent = nullptr);
    ~ContentTypeWidgetTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldChangeComboBoxIndex();
    void shouldEmitSignalWhenIndexChanged();
    void shouldChangeItem();
};

#endif // CONTENTTYPEWIDGETTEST_H
