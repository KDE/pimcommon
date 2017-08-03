/*
  Copyright (c) 2017 Montel Laurent <montel@kde.org>

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

#ifndef LOGACTIVITIESWIDGET_H
#define LOGACTIVITIESWIDGET_H

#include <QWidget>
#include "pimcommon_private_export.h"
class QPlainTextEdit;
namespace KPIMTextEdit {
class PlainTextEditorWidget;
}
namespace PimCommon {
class PIMCOMMON_TESTS_EXPORT LogActivitiesWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LogActivitiesWidget(QWidget *parent = nullptr);
    ~LogActivitiesWidget();
    void setLog(const QString &str);
    QString log() const;
    void clear();
    void addLogEntry(const QString &entry);
Q_SIGNALS:
    void textChanged(bool changed);

private:
    void slotTextChanged();
    KPIMTextEdit::PlainTextEditorWidget *mLog;
};
}

#endif // LOGACTIVITIESWIDGET_H
