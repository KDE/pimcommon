/*
  SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "lingvaengineclient.h"
#include <KLocalizedString>

LingvaEngineClient::LingvaEngineClient(QObject *parent)
    : PimCommonTextTranslator::TranslatorEngineClient{parent}
{
}

LingvaEngineClient::~LingvaEngineClient() = default;

QString LingvaEngineClient::name() const
{
    return QStringLiteral("google");
}

QString LingvaEngineClient::translatedName() const
{
    return i18n("Google");
}

PimCommonTextTranslator::TranslatorEnginePlugin *LingvaEngineClient::createTranslator()
{
    // TODO
    return nullptr;
}

QVector<QPair<QString, QString>> LingvaEngineClient::supportedLanguages()
{
    // TODO
    return {};
}
