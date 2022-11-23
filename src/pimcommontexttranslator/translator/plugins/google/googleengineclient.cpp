/*
  SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "googleengineclient.h"
#include <KLocalizedString>

GoogleEngineClient::GoogleEngineClient(QObject *parent)
    : PimCommonTextTranslator::TranslatorEngineClient{parent}
{
}

GoogleEngineClient::~GoogleEngineClient() = default;

QString GoogleEngineClient::name() const
{
    return QStringLiteral("google");
}

QString GoogleEngineClient::translatedName() const
{
    return i18n("Google");
}

PimCommonTextTranslator::TranslatorEnginePlugin *GoogleEngineClient::createTranslator()
{
    // TODO
    return nullptr;
}

QVector<QPair<QString, QString>> GoogleEngineClient::supportedLanguages()
{
    // TODO
    return {};
}
