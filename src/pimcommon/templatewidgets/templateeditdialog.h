/*
  SPDX-FileCopyrightText: 2013-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QDialog>

class QLineEdit;
namespace TextCustomEditor
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
    [[nodiscard]] QString templateName() const;

    void setScript(const QString &);
    [[nodiscard]] QString script() const;

private:
    void slotTemplateChanged();
    void readConfig();
    void writeConfig();
    TextCustomEditor::PlainTextEditorWidget *const mTextEdit;
    QLineEdit *const mTemplateNameEdit;
    QPushButton *mOkButton = nullptr;
};
}
