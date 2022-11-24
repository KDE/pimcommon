/*
  SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "libretranslateengineclient.h"
#include <KLocalizedString>

LibreTranslateEngineClient::LibreTranslateEngineClient(QObject *parent)
    : PimCommonTextTranslator::TranslatorEngineClient{parent}
{
}

LibreTranslateEngineClient::~LibreTranslateEngineClient() = default;

QString LibreTranslateEngineClient::name() const
{
    return QStringLiteral("google");
}

QString LibreTranslateEngineClient::translatedName() const
{
    return i18n("Google");
}

PimCommonTextTranslator::TranslatorEnginePlugin *LibreTranslateEngineClient::createTranslator()
{
    // TODO
    return nullptr;
}

QVector<QPair<QString, QString>> LibreTranslateEngineClient::supportedLanguages()
{
    // TODO
    return {};
}
