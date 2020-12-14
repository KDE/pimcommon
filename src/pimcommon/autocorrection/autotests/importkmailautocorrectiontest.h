/*
  SPDX-FileCopyrightText: 2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#ifndef IMPORTKMAILAUTOCORRECTIONTEST_H
#define IMPORTKMAILAUTOCORRECTIONTEST_H

#include <QObject>

class ImportKMailAutocorrectionTest : public QObject
{
    Q_OBJECT
public:
    explicit ImportKMailAutocorrectionTest(QObject *parent = nullptr);
    ~ImportKMailAutocorrectionTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};

#endif // IMPORTKMAILAUTOCORRECTIONTEST_H
