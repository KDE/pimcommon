/*
   SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "grammaraction.h"
#include "grammarerror.h"
#include "pimcommontextgrammar_export.h"

#include <QTextFormat>
namespace PimCommonTextGrammar
{
namespace GrammarResultUtil
{
enum TextInfo {
    ReplaceFormatInfo = QTextFormat::UserProperty + 1,
};
PIMCOMMONTEXTGRAMMAR_EXPORT void
applyGrammarResult(const QVector<PimCommonTextGrammar::GrammarError> &infos, QTextDocument *document, const QColor &negativeTextColor);
PIMCOMMONTEXTGRAMMAR_EXPORT void replaceWord(const PimCommonTextGrammar::GrammarAction &act, const QString &replacementWord, QTextDocument *document);
}
}
