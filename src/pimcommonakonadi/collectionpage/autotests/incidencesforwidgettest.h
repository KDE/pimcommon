/*
  SPDX-FileCopyrightText: 2014-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/
#ifndef INCIDENCESFORWIDGETTEST_H
#define INCIDENCESFORWIDGETTEST_H

#include <QObject>

class IncidencesForWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit IncidencesForWidgetTest(QObject *parent = nullptr);
    ~IncidencesForWidgetTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldChangeComboBoxIndex();
    void shouldEmitSignalWhenIndexChanged();
};

#endif // INCIDENCESFORWIDGETTEST_H
