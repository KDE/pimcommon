/*
  SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "yandexengineplugin.h"

YandexEnginePlugin::YandexEnginePlugin(QObject *parent)
    : PimCommonTextTranslator::TranslatorEnginePlugin(parent)
{
}

YandexEnginePlugin::~YandexEnginePlugin() = default;

void YandexEnginePlugin::translate()
{
    // TODO
}
