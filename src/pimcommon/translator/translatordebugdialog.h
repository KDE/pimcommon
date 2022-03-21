/*
  SPDX-FileCopyrightText: 2013-2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QDialog>

namespace KPIMTextEdit
{
class PlainTextEditorWidget;
}
class TranslatorDebugDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TranslatorDebugDialog(QWidget *parent = nullptr);
    ~TranslatorDebugDialog() override;

    void setDebug(const QString &debugStr);

private:
    void slotSaveAs();
    void readConfig();
    void writeConfig();
    KPIMTextEdit::PlainTextEditorWidget *const mEdit;
    QPushButton *mUser1Button = nullptr;
};
