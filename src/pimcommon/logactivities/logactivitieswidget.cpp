/*
  SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "logactivitieswidget.h"
#include <QVBoxLayout>
#include <KPIMTextEdit/PlainTextEditorWidget>
#include <KPIMTextEdit/PlainTextEditor>
using namespace PimCommon;

LogActivitiesWidget::LogActivitiesWidget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));

    mLog = new KPIMTextEdit::PlainTextEditorWidget(this);
    mLog->setObjectName(QStringLiteral("log"));
    mLog->setReadOnly(true);
    mainLayout->addWidget(mLog);
    connect(mLog->editor(), &KPIMTextEdit::PlainTextEditor::textChanged, this, &LogActivitiesWidget::slotTextChanged);
}

LogActivitiesWidget::~LogActivitiesWidget()
{
    disconnect(mLog->editor(), &KPIMTextEdit::PlainTextEditor::textChanged, this, &LogActivitiesWidget::slotTextChanged);
}

void LogActivitiesWidget::slotTextChanged()
{
    Q_EMIT textChanged(!mLog->editor()->document()->isEmpty());
}

void LogActivitiesWidget::addLogEntry(const QString &entry)
{
    mLog->editor()->appendHtml(entry);
}

void LogActivitiesWidget::setLog(const QString &str)
{
    mLog->setPlainText(str);
}

QString LogActivitiesWidget::log() const
{
    return mLog->toPlainText();
}

void LogActivitiesWidget::clear()
{
    mLog->clear();
}

KPIMTextEdit::PlainTextEditor *LogActivitiesWidget::editor()
{
    return mLog->editor();
}
