/*
  SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef TEST_CUSTOMTOOLSWIDGETNG_GUI_H
#define TEST_CUSTOMTOOLSWIDGETNG_GUI_H

#include <QWidget>
namespace PimCommon {
class CustomToolsWidgetNg;
}

class CustomToolWidgetNgTest : public QWidget
{
    Q_OBJECT
public:
    explicit CustomToolWidgetNgTest(QWidget *parent = nullptr);
    ~CustomToolWidgetNgTest();

private:
    PimCommon::CustomToolsWidgetNg *mCustomTools;
};

#endif
