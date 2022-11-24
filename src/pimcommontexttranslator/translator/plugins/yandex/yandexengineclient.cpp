/*
  SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "yandexengineclient.h"
#include <KLocalizedString>

YandexEngineClient::YandexEngineClient(QObject *parent)
    : PimCommonTextTranslator::TranslatorEngineClient{parent}
{
}

YandexEngineClient::~YandexEngineClient() = default;

QString YandexEngineClient::name() const
{
    return QStringLiteral("google");
}

QString YandexEngineClient::translatedName() const
{
    return i18n("Google");
}

PimCommonTextTranslator::TranslatorEnginePlugin *YandexEngineClient::createTranslator()
{
    // TODO
    return nullptr;
}

QVector<QPair<QString, QString>> YandexEngineClient::supportedLanguages()
{
    // TODO
    return {};
}
