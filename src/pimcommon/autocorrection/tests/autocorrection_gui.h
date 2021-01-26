/*
  SPDX-FileCopyrightText: 2013-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef TEST_AUTOCORRECTION_GUI_H
#define TEST_AUTOCORRECTION_GUI_H

#include <KSharedConfig>
#include <QDialog>
#include <QWidget>

#include <QTextEdit>

namespace PimCommon
{
class AutoCorrection;
class AutoCorrectionWidget;
class LineEditWithAutoCorrection;
}

class ConfigureTestDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ConfigureTestDialog(PimCommon::AutoCorrection *autoCorrection, QWidget *parent = nullptr);
    ~ConfigureTestDialog();

private Q_SLOTS:
    void slotSaveSettings();

private:
    PimCommon::AutoCorrectionWidget *mWidget = nullptr;
};

class TextEditAutoCorrectionWidget : public QTextEdit
{
    Q_OBJECT
public:
    explicit TextEditAutoCorrectionWidget(PimCommon::AutoCorrection *autoCorrection, QWidget *parent = nullptr);
    ~TextEditAutoCorrectionWidget() override;

protected:
    void keyPressEvent(QKeyEvent *e) override;

private:
    PimCommon::AutoCorrection *mAutoCorrection = nullptr;
};

class AutocorrectionTestWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AutocorrectionTestWidget(QWidget *parent = nullptr);
    ~AutocorrectionTestWidget();

private Q_SLOTS:
    void slotConfigure();
    void slotChangeMode(bool);

private:
    TextEditAutoCorrectionWidget *mEdit = nullptr;
    PimCommon::LineEditWithAutoCorrection *mSubject = nullptr;
    PimCommon::AutoCorrection *mAutoCorrection = nullptr;
    KSharedConfig::Ptr mConfig;
};

#endif
