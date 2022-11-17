/*
   SPDX-FileCopyrightText: 2019-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "grammalecteresultjob.h"
#include "pimcommontextgrammarcheck_export.h"
#include <PimCommonTextGrammarCheck/GrammarResultWidget>
namespace PimCommonTextGrammarCheck
{
class GrammalecteResultJob;
class PIMCOMMONTEXTGRAMMARCHECK_EXPORT GrammalecteResultWidget : public GrammarResultWidget
{
    Q_OBJECT
public:
    explicit GrammalecteResultWidget(QWidget *parent = nullptr);
    ~GrammalecteResultWidget() override;
    void checkGrammar() override;

private:
    void slotCheckGrammarFinished(const QString &result);
    void slotError(GrammalecteResultJob::ErrorType error);
};
}
