/*
  SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <PimCommonTextTranslator/TranslatorEnginePlugin>

class DeeplEnginePlugin : public PimCommonTextTranslator::TranslatorEnginePlugin
{
public:
    DeeplEnginePlugin();
    ~DeeplEnginePlugin() override;

    void translate() override;
};
