/*
  SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef LOGACTIVITIESWIDGET_H
#define LOGACTIVITIESWIDGET_H

#include <QWidget>
#include "pimcommon_private_export.h"
namespace KPIMTextEdit {
class PlainTextEditorWidget;
class PlainTextEditor;
}
namespace PimCommon {
class PIMCOMMON_TESTS_EXPORT LogActivitiesWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LogActivitiesWidget(QWidget *parent = nullptr);
    ~LogActivitiesWidget();
    void setLog(const QString &str);
    Q_REQUIRED_RESULT QString log() const;
    void clear();
    void addLogEntry(const QString &entry);
    Q_REQUIRED_RESULT KPIMTextEdit::PlainTextEditor *editor();
Q_SIGNALS:
    void textChanged(bool changed);

private:
    void slotTextChanged();
    KPIMTextEdit::PlainTextEditorWidget *mLog = nullptr;
};
}

#endif // LOGACTIVITIESWIDGET_H
