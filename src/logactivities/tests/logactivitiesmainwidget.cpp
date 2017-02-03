/*
   Copyright (C) 2017 Laurent Montel <montel@kde.org>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "logactivitiesmainwidget.h"
#include "logactivities/logactivitiesdialog.h"
#include "logactivities/logactivitiesmanager.h"
#include <QPushButton>
#include <QHBoxLayout>

LogActivitiesMainWidget::LogActivitiesMainWidget(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    QPushButton *button = new QPushButton(QStringLiteral("Open Log"), this);
    connect(button, &QPushButton::clicked, this, &LogActivitiesMainWidget::slotOpenDialog);
    mainLayout->addWidget(button);
    PimCommon::LogActivitiesManager::self()->setEnableLogActivities(true);
    PimCommon::LogActivitiesManager::self()->appendLog(QStringLiteral("foo"));
}

void LogActivitiesMainWidget::slotOpenDialog()
{
    PimCommon::LogActivitiesManager::self()->showLogActivitiesDialog();
}
