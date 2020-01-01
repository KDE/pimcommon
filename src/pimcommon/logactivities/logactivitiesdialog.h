/*
  Copyright (C) 2017-2020 Laurent Montel <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef LOGACTIVITIESDIALOG_H
#define LOGACTIVITIESDIALOG_H

#include <QDialog>
#include "pimcommon_private_export.h"
class QPushButton;
class QCheckBox;
namespace PimCommon {
class LogActivitiesWidget;
class PIMCOMMON_TESTS_EXPORT LogActivitiesDialog : public QDialog
{
    Q_OBJECT
public:
    explicit LogActivitiesDialog(QWidget *parent = nullptr);
    ~LogActivitiesDialog();

    void setLog(const QString &str);

Q_SIGNALS:
    void logCleared();

private:
    void slotSave();
    void slotClear();
    void readConfig();
    void writeConfig();
    void slotLogEntryCleared();
    void slotLogEntryAdded(const QString &entry);
    void slotEnableLogActivities(bool state);
    void slotActivityTextChanged(bool changed);

    LogActivitiesWidget *mLogWidget = nullptr;
    QPushButton *mClearButton = nullptr;
    QCheckBox *mEnableLogActivities = nullptr;
    QPushButton *mSaveButton = nullptr;
    QPushButton *mShareButton = nullptr;
};
}

#endif // LOGACTIVITIESDIALOG_H
