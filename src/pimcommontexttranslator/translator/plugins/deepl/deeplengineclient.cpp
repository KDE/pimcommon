/*
  SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "deeplengineclient.h"
#include <KLocalizedString>

DeeplEngineClient::DeeplEngineClient(QObject *parent)
    : PimCommonTextTranslator::TranslatorEngineClient{parent}
{
}

DeeplEngineClient::~DeeplEngineClient() = default;

QString DeeplEngineClient::name() const
{
    return QStringLiteral("google");
}

QString DeeplEngineClient::translatedName() const
{
    return i18n("Google");
}

PimCommonTextTranslator::TranslatorEnginePlugin *DeeplEngineClient::createTranslator()
{
    // TODO
    return nullptr;
}

QVector<QPair<QString, QString>> DeeplEngineClient::supportedLanguages()
{
    // TODO
    return {};
}
