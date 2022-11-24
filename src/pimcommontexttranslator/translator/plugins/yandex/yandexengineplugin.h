/*
  SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <PimCommonTextTranslator/TranslatorEnginePlugin>

class YandexEnginePlugin : public PimCommonTextTranslator::TranslatorEnginePlugin
{
public:
    YandexEnginePlugin();
    ~YandexEnginePlugin() override;

    void translate() override;
};
