/*
  SPDX-FileCopyrightText: 2018-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "widgets/purposemenuwidget.h"
#include <QObject>
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
    ~PurposeMenuWidgetTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};
