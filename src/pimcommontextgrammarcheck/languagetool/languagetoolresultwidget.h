/*
   SPDX-FileCopyrightText: 2019-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "common/grammarresultwidget.h"
#include "pimcommontextgrammarcheck_export.h"
namespace PimCommonTextGrammarCheck
{
class LanguageToolComboBox;
class LanguageToolUpdateComboBox;
class PIMCOMMONTEXTGRAMMARCHECK_EXPORT LanguageToolResultWidget : public GrammarResultWidget
{
    Q_OBJECT
public:
    explicit LanguageToolResultWidget(QWidget *parent = nullptr);
    ~LanguageToolResultWidget() override;
    void checkGrammar() override;

protected:
    void addExtraWidget() override;

private:
    Q_DISABLE_COPY(LanguageToolResultWidget)
    void slotCheckGrammarFinished(const QString &result);
    void slotError(const QString &str);
    LanguageToolComboBox *mLanguageToolComboBox = nullptr;
    LanguageToolUpdateComboBox *const mLanguageToolUpdateCombobox;
};
}
