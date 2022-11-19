/*
   SPDX-FileCopyrightText: 2019-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "languageinfo.h"
#include "pimcommontextgrammarcheckprivate_export.h"
#include <QVector>
namespace PimCommonTextGrammarCheck
{
class PIMCOMMONTEXTGRAMMARCHECK_TESTS_EXPORT LanguageToolListOfLanguagesParser
{
public:
    LanguageToolListOfLanguagesParser();
    ~LanguageToolListOfLanguagesParser();
    Q_REQUIRED_RESULT QVector<LanguageInfo> parseResult(const QJsonArray &obj) const;
};
}
