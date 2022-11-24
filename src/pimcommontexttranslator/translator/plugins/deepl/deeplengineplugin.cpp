/*
  SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "deeplengineplugin.h"

DeeplEnginePlugin::DeeplEnginePlugin(QObject *parent)
    : PimCommonTextTranslator::TranslatorEnginePlugin(parent)
{
}

DeeplEnginePlugin::~DeeplEnginePlugin() = default;

void DeeplEnginePlugin::translate()
{
    // TODO
}
