/*
  SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
  Code based on Digikam donlinetranslator
*/

#include "libretranslatetranslator.h"
#include <KLocalizedString>

using namespace PimCommon;
LibreTranslateTranslator::LibreTranslateTranslator(QObject *parent)
    : TranslatorEngineBase{parent}
{
}

LibreTranslateTranslator::~LibreTranslateTranslator() = default;

QString LibreTranslateTranslator::engineName() const
{
    return i18n("Libre Translate");
}

void LibreTranslateTranslator::translate()
{
    // TODO
}

QVector<QPair<QString, QString>> LibreTranslateTranslator::supportedLanguage() const
{
    return {};
}

void LibreTranslateTranslator::translateText()
{
}
