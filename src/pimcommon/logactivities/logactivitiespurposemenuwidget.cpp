/*
   SPDX-FileCopyrightText: 2018-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "logactivitiespurposemenuwidget.h"
#include <KPIMTextEdit/PlainTextEditor>

using namespace PimCommon;
LogactivitiesPurposeMenuWidget::LogactivitiesPurposeMenuWidget(QWidget *parentWidget, QObject *parent)
    : PimCommon::PurposeMenuWidget(parentWidget, parent)
{
}

LogactivitiesPurposeMenuWidget::~LogactivitiesPurposeMenuWidget()
{
}

QByteArray LogactivitiesPurposeMenuWidget::text()
{
    if (mEditor) {
        return mEditor->toPlainText().toUtf8();
    }
    return {};
}

void LogactivitiesPurposeMenuWidget::setEditorWidget(KPIMTextEdit::PlainTextEditor *editor)
{
    mEditor = editor;
}
