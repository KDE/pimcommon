/*
   SPDX-FileCopyrightText: 2019-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "pimcommontextgrammarcheckprivate_export.h"
#include <PimCommonTextGrammarCheck/GrammarError>
#include <QJsonObject>
#include <QVector>
namespace PimCommonTextGrammarCheck
{
class PIMCOMMONTEXTGRAMMARCHECK_TESTS_EXPORT GrammalecteParser
{
public:
    GrammalecteParser();
    ~GrammalecteParser();
    Q_REQUIRED_RESULT QVector<GrammarError> parseResult(const QJsonObject &obj) const;
};
}
