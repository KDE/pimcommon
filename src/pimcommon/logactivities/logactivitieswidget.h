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
