/*
   SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QObject>

class AddresseeLineEditUtilTest : public QObject
{
    Q_OBJECT
public:
    explicit AddresseeLineEditUtilTest(QObject *parent = nullptr);
    ~AddresseeLineEditUtilTest() override;

private Q_SLOTS:
    void shouldAdaptPasteMails_data();
    void shouldAdaptPasteMails();
};
