/*
  SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "googleengineclient.h"

GoogleEngineClient::GoogleEngineClient(QObject *parent)
    : PimCommonTextTranslator::TranslatorEngineClient{parent}
{
}

GoogleEngineClient::~GoogleEngineClient() = default;

QString GoogleEngineClient::name() const
{
    // TODO
    return {};
}

QString GoogleEngineClient::translatedName() const
{
    // TODO
    return {};
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
