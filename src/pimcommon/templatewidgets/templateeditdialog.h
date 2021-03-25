/*
  SPDX-FileCopyrightText: 2013-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QDialog>

class QLineEdit;
namespace KPIMTextEdit
{
class PlainTextEditorWidget;
}
namespace PimCommon
{
class TemplateEditDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TemplateEditDialog(QWidget *parent = nullptr, bool defaultTemplate = false);
    ~TemplateEditDialog() override;

    void setTemplateName(const QString &name);
    Q_REQUIRED_RESULT QString templateName() const;

    void setScript(const QString &);
    Q_REQUIRED_RESULT QString script() const;

private:
    void slotTemplateChanged();
    void readConfig();
    void writeConfig();
    KPIMTextEdit::PlainTextEditorWidget *mTextEdit = nullptr;
    QLineEdit *mTemplateNameEdit = nullptr;
    QPushButton *mOkButton = nullptr;
};
}

