/*
  SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef LOGACTIVITIESDIALOG_H
#define LOGACTIVITIESDIALOG_H

#include "pimcommon_private_export.h"
#include <QDialog>
class QPushButton;
class QCheckBox;
namespace PimCommon
{
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
