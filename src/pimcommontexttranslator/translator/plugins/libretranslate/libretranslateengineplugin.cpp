/*
  SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "libretranslateengineplugin.h"

LibreTranslateEnginePlugin::LibreTranslateEnginePlugin(QObject *parent)
    : PimCommonTextTranslator::TranslatorEnginePlugin(parent)
{
}

LibreTranslateEnginePlugin::~LibreTranslateEnginePlugin() = default;

void LibreTranslateEnginePlugin::translate()
{
    // TODO
}
