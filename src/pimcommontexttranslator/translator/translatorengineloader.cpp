/*
  SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "translatorengineloader.h"
using namespace PimCommonTextTranslator;
TranslatorEngineLoader::TranslatorEngineLoader(QObject *parent)
    : QObject{parent}
{
}

TranslatorEngineLoader::~TranslatorEngineLoader() = default;
