/*
   SPDX-FileCopyrightText: 2019-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QWidget>

#include "common/grammaraction.h"
class QNetworkAccessManager;
namespace PimCommonTextGrammarCheck
{
class LanguageToolResultWidget;
}
class QTextEdit;
class LanguageToolWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LanguageToolWidget(QWidget *parent = nullptr);
    ~LanguageToolWidget() override;

private:
    void slotReplaceText(const PimCommonTextGrammarCheck::GrammarAction &act);
    void slotCheckGrammar();
    void slotError();
    void slotGetListOfLanguages();
    void slotResultFinished(const QString &result);
    void slotGetLanguagesError();
    void slotGetLanguagesFinished(const QString &result);
    QTextEdit *mInput = nullptr;
    PimCommonTextGrammarCheck::LanguageToolResultWidget *mResultWidget = nullptr;
    QNetworkAccessManager *mNetworkAccessManager = nullptr;
};
