/*
  SPDX-FileCopyrightText: 2013-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <KSharedConfig>
#include <QDialog>
#include <QWidget>

#include <QTextEdit>
#ifdef HAVE_KTEXTADDONS_TEXT_AUTOCORRECTION_SUPPORT
namespace TextAutoCorrection
{
class AutoCorrection;
class AutoCorrectionWidget;
}
#else
namespace PimCommonAutoCorrection
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
#ifdef HAVE_KTEXTADDONS_TEXT_AUTOCORRECTION_SUPPORT
    explicit ConfigureTestDialog(TextAutoCorrection::AutoCorrection *autoCorrection, QWidget *parent = nullptr);
#else
    explicit ConfigureTestDialog(PimCommonAutoCorrection::AutoCorrection *autoCorrection, QWidget *parent = nullptr);
#endif
    ~ConfigureTestDialog() override;

private Q_SLOTS:
    void slotSaveSettings();

private:
#ifdef HAVE_KTEXTADDONS_TEXT_AUTOCORRECTION_SUPPORT
    TextAutoCorrection::AutoCorrectionWidget *mWidget = nullptr;
#else
    PimCommonAutoCorrection::AutoCorrectionWidget *mWidget = nullptr;
#endif
};

class TextEditAutoCorrectionWidget : public QTextEdit
{
    Q_OBJECT
public:
#ifdef HAVE_KTEXTADDONS_TEXT_AUTOCORRECTION_SUPPORT
    explicit TextEditAutoCorrectionWidget(TextAutoCorrection::AutoCorrection *autoCorrection, QWidget *parent = nullptr);
#else
    explicit TextEditAutoCorrectionWidget(PimCommonAutoCorrection::AutoCorrection *autoCorrection, QWidget *parent = nullptr);
#endif
    ~TextEditAutoCorrectionWidget() override;

protected:
    void keyPressEvent(QKeyEvent *e) override;

private:
#ifdef HAVE_KTEXTADDONS_TEXT_AUTOCORRECTION_SUPPORT
    TextAutoCorrection::AutoCorrection *mAutoCorrection = nullptr;
#else
    PimCommonAutoCorrection::AutoCorrection *mAutoCorrection = nullptr;
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
#ifdef HAVE_KTEXTADDONS_TEXT_AUTOCORRECTION_SUPPORT
    TextAutoCorrection::AutoCorrection *mAutoCorrection = nullptr;
#else
    PimCommonAutoCorrection::AutoCorrection *mAutoCorrection = nullptr;
#endif
    KSharedConfig::Ptr mConfig;
};
