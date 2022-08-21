/*
  SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "bingtranslator.h"
using namespace PimCommon;
QByteArray BingTranslator::sBingKey;
QByteArray BingTranslator::sBingToken;
QString BingTranslator::sBingIg;
QString BingTranslator::sBingIid;
BingTranslator::BingTranslator(QObject *parent)
    : TranslatorEngineBase{parent}
{
}

BingTranslator::~BingTranslator() = default;

void BingTranslator::translate()
{
    if (sBingKey.isEmpty() || sBingToken.isEmpty()) {
        // => get
    }
    // TODO
}
