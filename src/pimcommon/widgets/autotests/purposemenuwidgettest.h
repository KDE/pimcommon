/*
  Copyright (c) 2018-2019 Montel Laurent <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License, version 2, as
  published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
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
