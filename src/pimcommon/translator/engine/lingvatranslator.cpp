/*
  SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
  Code based on Digikam donlinetranslator
*/

#include "lingvatranslator.h"
#include <KLocalizedString>
using namespace PimCommon;
LingvaTranslator::LingvaTranslator(QObject *parent)
    : TranslatorEngineBase{parent}
{
}

LingvaTranslator::~LingvaTranslator() = default;

QString PimCommon::LingvaTranslator::engineName() const
{
    return i18n("Lingva");
}

void PimCommon::LingvaTranslator::translate()
{
}

QVector<QPair<QString, QString>> PimCommon::LingvaTranslator::supportedLanguage() const
{
    return {};
}
