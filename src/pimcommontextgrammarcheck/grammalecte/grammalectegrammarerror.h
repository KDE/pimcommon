/*
   SPDX-FileCopyrightText: 2019-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "pimcommontextgrammarcheckprivate_export.h"
#include <PimCommonTextGrammarCheck/GrammarError>
namespace PimCommonTextGrammarCheck
{
class PIMCOMMONTEXTGRAMMARCHECK_TESTS_EXPORT GrammalecteGrammarError : public GrammarError
{
public:
    GrammalecteGrammarError();
    ~GrammalecteGrammarError() override;
    void parse(const QJsonObject &obj, int blockindex) override;

private:
    Q_REQUIRED_RESULT static QStringList parseSuggestion(const QJsonObject &obj);
    Q_REQUIRED_RESULT static QColor parseColor(const QJsonObject &obj);
};
}
Q_DECLARE_METATYPE(PimCommonTextGrammarCheck::GrammalecteGrammarError)
Q_DECLARE_TYPEINFO(PimCommonTextGrammarCheck::GrammalecteGrammarError, Q_MOVABLE_TYPE);
