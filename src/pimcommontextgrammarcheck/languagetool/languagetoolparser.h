/*
   SPDX-FileCopyrightText: 2019-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "pimcommontextgrammarcheckprivate_export.h"

#include "common/grammarerror.h"
namespace PimCommonTextGrammar
{
class PIMCOMMONTEXTGRAMMAR_TESTS_EXPORT LanguageToolParser
{
public:
    LanguageToolParser();
    ~LanguageToolParser();
    Q_REQUIRED_RESULT QVector<PimCommonTextGrammar::GrammarError> parseResult(const QJsonObject &obj) const;
};
}
