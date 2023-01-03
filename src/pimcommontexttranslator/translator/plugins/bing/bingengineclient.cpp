/*
  SPDX-FileCopyrightText: 2022-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "bingengineclient.h"
#include "bingengineplugin.h"
#include "translator/misc/translatorutil.h"
#include <KLocalizedString>

BingEngineClient::BingEngineClient(QObject *parent)
    : PimCommonTextTranslator::TranslatorEngineClient{parent}
{
}

BingEngineClient::~BingEngineClient() = default;

QString BingEngineClient::name() const
{
    return QStringLiteral("bing");
}

QString BingEngineClient::translatedName() const
{
    return i18n("Bing");
}

PimCommonTextTranslator::TranslatorEnginePlugin *BingEngineClient::createTranslator()
{
    return new BingEnginePlugin();
}

QMap<PimCommonTextTranslator::TranslatorUtil::Language, QString> BingEngineClient::supportedLanguages()
{
    if (mLanguages.isEmpty()) {
        mLanguages = fillLanguages();
    }
    return mLanguages;
}

bool BingEngineClient::isSupported(PimCommonTextTranslator::TranslatorUtil::Language lang) const
{
    return true;
}
