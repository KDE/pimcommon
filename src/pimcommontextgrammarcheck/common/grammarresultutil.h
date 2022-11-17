/*
   SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "grammaraction.h"
#include "grammarerror.h"
#include "pimcommontextgrammarcheck_export.h"

#include <QTextFormat>
namespace PimCommonTextGrammarCheck
{
namespace GrammarResultUtil
{
enum TextInfo {
    ReplaceFormatInfo = QTextFormat::UserProperty + 1,
};
PIMCOMMONTEXTGRAMMARCHECK_EXPORT void
applyGrammarResult(const QVector<PimCommonTextGrammarCheck::GrammarError> &infos, QTextDocument *document, const QColor &negativeTextColor);
PIMCOMMONTEXTGRAMMARCHECK_EXPORT void replaceWord(const PimCommonTextGrammarCheck::GrammarAction &act, const QString &replacementWord, QTextDocument *document);
}
}
