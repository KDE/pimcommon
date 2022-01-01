/*
  SPDX-FileCopyrightText: 2017-2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "pimcommon_private_export.h"
#include <QWidget>
namespace KPIMTextEdit
{
class PlainTextEditorWidget;
class PlainTextEditor;
}
namespace PimCommon
{
class PIMCOMMON_TESTS_EXPORT LogActivitiesWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LogActivitiesWidget(QWidget *parent = nullptr);
    ~LogActivitiesWidget() override;
    void setLog(const QString &str);
    Q_REQUIRED_RESULT QString log() const;
    void clear();
    void addLogEntry(const QString &entry);
    Q_REQUIRED_RESULT KPIMTextEdit::PlainTextEditor *editor();
Q_SIGNALS:
    void textChanged(bool changed);

private:
    void slotTextChanged();
    KPIMTextEdit::PlainTextEditorWidget *const mLog;
};
}

