/*
  SPDX-FileCopyrightText: 2013-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef TRANSLATORDEBUGDIALOG_H
#define TRANSLATORDEBUGDIALOG_H

#include <QDialog>

namespace KPIMTextEdit {
class PlainTextEditorWidget;
}
class TranslatorDebugDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TranslatorDebugDialog(QWidget *parent = nullptr);
    ~TranslatorDebugDialog();

    void setDebug(const QString &debugStr);

private:
    void slotSaveAs();
    void readConfig();
    void writeConfig();
    KPIMTextEdit::PlainTextEditorWidget *mEdit = nullptr;
    QPushButton *mUser1Button = nullptr;
};

#endif // TRANSLATORDEBUGDIALOG_H
