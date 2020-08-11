/*
   SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef LOGACTIVITIESMAINWIDGET_H
#define LOGACTIVITIESMAINWIDGET_H

#include <QWidget>

class LogActivitiesMainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LogActivitiesMainWidget(QWidget *parent = nullptr);
    ~LogActivitiesMainWidget() = default;

private:
    void slotOpenDialog();
    void slotClearLog();
    void slotEnableLogActivities(bool enable);
    void slotAddLog();
};

#endif // LOGACTIVITIESMAINWIDGET_H
