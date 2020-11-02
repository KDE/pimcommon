/*
   SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "logactivitiesmainwidget.h"
#include "logactivities/logactivitiesdialog.h"
#include "logactivities/logactivitiesmanager.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QCheckBox>

LogActivitiesMainWidget::LogActivitiesMainWidget(QWidget *parent)
    : QWidget(parent)
{
    auto *mainLayout = new QHBoxLayout(this);
    QPushButton *button = new QPushButton(QStringLiteral("Open Log"), this);
    connect(button, &QPushButton::clicked, this, &LogActivitiesMainWidget::slotOpenDialog);
    mainLayout->addWidget(button);

    QPushButton *addLog = new QPushButton(QStringLiteral("Append Log"), this);
    connect(addLog, &QPushButton::clicked, this, &LogActivitiesMainWidget::slotAddLog);
    mainLayout->addWidget(addLog);

    QPushButton *clearLogButton = new QPushButton(QStringLiteral("Clear log"), this);
    connect(clearLogButton, &QPushButton::clicked, this, &LogActivitiesMainWidget::slotClearLog);
    mainLayout->addWidget(clearLogButton);

    QCheckBox *enableLog = new QCheckBox(QStringLiteral("Enable Log Activities"), this);
    connect(enableLog, &QPushButton::toggled, this, &LogActivitiesMainWidget::slotEnableLogActivities);
    enableLog->setChecked(true);
    mainLayout->addWidget(enableLog);

    PimCommon::LogActivitiesManager::self()->setEnableLogActivities(true);
    PimCommon::LogActivitiesManager::self()->appendLog(QStringLiteral("foo"));
}

void LogActivitiesMainWidget::slotOpenDialog()
{
    PimCommon::LogActivitiesManager::self()->showLogActivitiesDialog();
}

void LogActivitiesMainWidget::slotClearLog()
{
    PimCommon::LogActivitiesManager::self()->clear();
}

void LogActivitiesMainWidget::slotEnableLogActivities(bool enable)
{
    PimCommon::LogActivitiesManager::self()->setEnableLogActivities(enable);
}

void LogActivitiesMainWidget::slotAddLog()
{
    PimCommon::LogActivitiesManager::self()->appendLog(QStringLiteral("Foo"));
}
