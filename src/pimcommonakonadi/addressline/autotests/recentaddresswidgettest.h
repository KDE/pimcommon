/*
  SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#ifndef RECENTADDRESSWIDGETTEST_H
#define RECENTADDRESSWIDGETTEST_H

#include <QObject>

class RecentAddressWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit RecentAddressWidgetTest(QObject *parent = nullptr);
    ~RecentAddressWidgetTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldAddAddresses();
    void shouldInformThatItWasChanged();
    void shouldNotAddMultiSameLine();
    void shouldNotAddEmptyLine();
    void shouldDisableAddButton();
};

#endif // RECENTADDRESSWIDGETTEST_H
