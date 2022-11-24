/*
  SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <PimCommonTextTranslator/TranslatorEnginePlugin>

class BingEnginePlugin : public PimCommonTextTranslator::TranslatorEnginePlugin
{
public:
    BingEnginePlugin();
    ~BingEnginePlugin() override;

    void translate() override;
};
