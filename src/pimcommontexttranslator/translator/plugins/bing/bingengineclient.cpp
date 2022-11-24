/*
  SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "bingengineclient.h"
#include <KLocalizedString>

BingEngineClient::BingEngineClient(QObject *parent)
    : PimCommonTextTranslator::TranslatorEngineClient{parent}
{
}

BingEngineClient::~BingEngineClient() = default;

QString BingEngineClient::name() const
{
    return QStringLiteral("google");
}

QString BingEngineClient::translatedName() const
{
    return i18n("Google");
}

PimCommonTextTranslator::TranslatorEnginePlugin *BingEngineClient::createTranslator()
{
    // TODO
    return nullptr;
}

QVector<QPair<QString, QString>> BingEngineClient::supportedLanguages()
{
    // TODO
    return {};
}
