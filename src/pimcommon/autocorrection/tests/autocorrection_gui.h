/*
  SPDX-FileCopyrightText: 2013-2024 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <KSharedConfig>
#include <QDialog>
#include <QWidget>

#include <QTextEdit>
namespace TextAutoCorrectionCore
{
class AutoCorrection;
}
namespace TextAutoCorrectionWidgets
{
class AutoCorrectionWidget;
}
namespace PimCommon
{
class LineEditWithAutoCorrection;
}
class ConfigureTestDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ConfigureTestDialog(TextAutoCorrectionCore::AutoCorrection *autoCorrection, QWidget *parent = nullptr);
    ~ConfigureTestDialog() override;

private Q_SLOTS:
    void slotSaveSettings();

private:
    TextAutoCorrectionWidgets::AutoCorrectionWidget *mWidget = nullptr;
};

class TextEditAutoCorrectionWidget : public QTextEdit
{
    Q_OBJECT
public:
    explicit TextEditAutoCorrectionWidget(TextAutoCorrectionCore::AutoCorrection *autoCorrection, QWidget *parent = nullptr);
    ~TextEditAutoCorrectionWidget() override;

protected:
    void keyPressEvent(QKeyEvent *e) override;

private:
    TextAutoCorrectionCore::AutoCorrection *mAutoCorrection = nullptr;
};

class AutocorrectionTestWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AutocorrectionTestWidget(QWidget *parent = nullptr);
    ~AutocorrectionTestWidget() override;

private Q_SLOTS:
    void slotConfigure();
    void slotChangeMode(bool);

private:
    TextEditAutoCorrectionWidget *mEdit = nullptr;
    PimCommon::LineEditWithAutoCorrection *mSubject = nullptr;
    TextAutoCorrectionCore::AutoCorrection *mAutoCorrection = nullptr;
    KSharedConfig::Ptr mConfig;
};
