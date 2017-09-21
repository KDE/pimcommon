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

#include "logactivitieswidget.h"
#include <QVBoxLayout>
#include <KPIMTextEdit/PlainTextEditorWidget>
#include <KPIMTextEdit/PlainTextEditor>
#include <QDebug>
using namespace PimCommon;

LogActivitiesWidget::LogActivitiesWidget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setMargin(0);
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
