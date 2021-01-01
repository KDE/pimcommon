/*
  SPDX-FileCopyrightText: 2018-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef PURPOSEMENUWIDGETTEST_H
#define PURPOSEMENUWIDGETTEST_H

#include <QObject>
#include "widgets/purposemenuwidget.h"
class TestMenu : public PimCommon::PurposeMenuWidget
{
    Q_OBJECT
public:
    TestMenu(QWidget *parentWidget, QObject *parent = nullptr)
        : PimCommon::PurposeMenuWidget(parentWidget, parent)
    {
    }

    QByteArray text() override
    {
        return "";
    }
};

class PurposeMenuWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit PurposeMenuWidgetTest(QObject *parent = nullptr);
    ~PurposeMenuWidgetTest() = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};

#endif // PURPOSEMENUWIDGETTEST_H
