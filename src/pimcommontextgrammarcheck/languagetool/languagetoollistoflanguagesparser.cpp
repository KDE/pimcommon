/*
   SPDX-FileCopyrightText: 2019-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "languagetoollistoflanguagesparser.h"

#include <QJsonArray>
#include <QJsonObject>
using namespace PimCommonTextGrammarCheck;
LanguageToolListOfLanguagesParser::LanguageToolListOfLanguagesParser() = default;

LanguageToolListOfLanguagesParser::~LanguageToolListOfLanguagesParser() = default;

QVector<LanguageInfo> LanguageToolListOfLanguagesParser::parseResult(const QJsonArray &array) const
{
    QVector<LanguageInfo> lstLanguageInfo;
    for (const QJsonValue &current : array) {
        // qDebug() << " current " << current;
        if (current.type() == QJsonValue::Object) {
            const QJsonObject languageToolObject = current.toObject();
            LanguageInfo lang;
            lang.parse(languageToolObject);
            if (lang.isValid()) {
                lstLanguageInfo.append(std::move(lang));
            }
        }
    }
    lstLanguageInfo.erase(std::unique(lstLanguageInfo.begin(), lstLanguageInfo.end()), lstLanguageInfo.end());
    return lstLanguageInfo;
}
