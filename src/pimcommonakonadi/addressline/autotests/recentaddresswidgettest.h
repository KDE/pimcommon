/*
  SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#pragma once

#include <QObject>

class RecentAddressWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit RecentAddressWidgetTest(QObject *parent = nullptr);
    ~RecentAddressWidgetTest() override;
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldAddAddresses();
    void shouldInformThatItWasChanged();
    void shouldNotAddMultiSameLine();
    void shouldNotAddEmptyLine();
    void shouldDisableAddButton();
};
