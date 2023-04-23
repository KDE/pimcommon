/*
  SPDX-FileCopyrightText: 2013-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <KSharedConfig>
#include <QDialog>
#include <QWidget>

#include "config-pimcommon.h"
#include <QTextEdit>
#if HAVE_TEXT_AUTOCORRECTION_WIDGETS
namespace TextAutoCorrectionCore
{
class AutoCorrection;
}
namespace TextAutoCorrectionWidgets
{
class AutoCorrectionWidget;
}
#else
namespace TextAutoCorrection
{
class AutoCorrection;
class AutoCorrectionWidget;
}
#endif
namespace PimCommon
{
class LineEditWithAutoCorrection;
}
class ConfigureTestDialog : public QDialog
{
    Q_OBJECT
public:
#if HAVE_TEXT_AUTOCORRECTION_WIDGETS
    explicit ConfigureTestDialog(TextAutoCorrectionCore::AutoCorrection *autoCorrection, QWidget *parent = nullptr);
#else
    explicit ConfigureTestDialog(TextAutoCorrection::AutoCorrection *autoCorrection, QWidget *parent = nullptr);
#endif
    ~ConfigureTestDialog() override;

private Q_SLOTS:
    void slotSaveSettings();

private:
#if HAVE_TEXT_AUTOCORRECTION_WIDGETS
    TextAutoCorrectionWidgets::AutoCorrectionWidget *mWidget = nullptr;
#else
    TextAutoCorrection::AutoCorrectionWidget *mWidget = nullptr;
#endif
};

class TextEditAutoCorrectionWidget : public QTextEdit
{
    Q_OBJECT
public:
#if HAVE_TEXT_AUTOCORRECTION_WIDGETS
    explicit TextEditAutoCorrectionWidget(TextAutoCorrectionCore::AutoCorrection *autoCorrection, QWidget *parent = nullptr);
#else
    explicit TextEditAutoCorrectionWidget(TextAutoCorrection::AutoCorrection *autoCorrection, QWidget *parent = nullptr);
#endif
    ~TextEditAutoCorrectionWidget() override;

protected:
    void keyPressEvent(QKeyEvent *e) override;

private:
#if HAVE_TEXT_AUTOCORRECTION_WIDGETS
    TextAutoCorrectionCore::AutoCorrection *mAutoCorrection = nullptr;
#else
    TextAutoCorrection::AutoCorrection *mAutoCorrection = nullptr;
#endif
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
#if HAVE_TEXT_AUTOCORRECTION_WIDGETS
    TextAutoCorrectionCore::AutoCorrection *mAutoCorrection = nullptr;
#else
    TextAutoCorrection::AutoCorrection *mAutoCorrection = nullptr;
#endif
    KSharedConfig::Ptr mConfig;
};
