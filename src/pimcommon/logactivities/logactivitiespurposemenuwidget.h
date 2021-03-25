/*
   SPDX-FileCopyrightText: 2018-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "widgets/purposemenuwidget.h"
namespace KPIMTextEdit
{
class PlainTextEditor;
}
namespace PimCommon
{
class LogactivitiesPurposeMenuWidget : public PimCommon::PurposeMenuWidget
{
    Q_OBJECT
public:
    explicit LogactivitiesPurposeMenuWidget(QWidget *parentWidget, QObject *parent = nullptr);
    ~LogactivitiesPurposeMenuWidget() override;

    QByteArray text() override;
    void setEditorWidget(KPIMTextEdit::PlainTextEditor *editor);

private:
    KPIMTextEdit::PlainTextEditor *mEditor = nullptr;
};
}

