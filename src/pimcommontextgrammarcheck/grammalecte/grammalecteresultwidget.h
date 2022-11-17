/*
   SPDX-FileCopyrightText: 2019-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "common/grammarresultwidget.h"
#include "grammalectegrammarerror.h"
#include "grammalecteresultjob.h"
#include "pimcommontextgrammar_export.h"
namespace PimCommonTextGrammar
{
class GrammalecteResultJob;
class PIMCOMMONTEXTGRAMMAR_EXPORT GrammalecteResultWidget : public GrammarResultWidget
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
