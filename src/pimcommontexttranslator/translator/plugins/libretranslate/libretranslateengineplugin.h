/*
  SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <PimCommonTextTranslator/TranslatorEnginePlugin>

class LibreTranslateEnginePlugin : public PimCommonTextTranslator::TranslatorEnginePlugin
{
public:
    LibreTranslateEnginePlugin();
    ~LibreTranslateEnginePlugin() override;

    void translate() override;
};
