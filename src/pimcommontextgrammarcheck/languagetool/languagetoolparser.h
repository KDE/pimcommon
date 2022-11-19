/*
   SPDX-FileCopyrightText: 2019-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "pimcommontextgrammarcheckprivate_export.h"

#include "common/grammarerror.h"
namespace PimCommonTextGrammarCheck
{
class PIMCOMMONTEXTGRAMMARCHECK_TESTS_EXPORT LanguageToolParser
{
public:
    LanguageToolParser();
    ~LanguageToolParser();
    Q_REQUIRED_RESULT QVector<PimCommonTextGrammarCheck::GrammarError> parseResult(const QJsonObject &obj) const;
};
}
