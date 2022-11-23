/*
  SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "translatorengineplugin.h"
using namespace PimCommonTextTranslator;

class PimCommonTextTranslator::TranslatorEnginePluginPrivate
{
public:
    QString mText;
    QString mFrom;
    QString mTo;
};

TranslatorEnginePlugin::TranslatorEnginePlugin()
    : d(new PimCommonTextTranslator::TranslatorEnginePluginPrivate)
{
}

TranslatorEnginePlugin::~TranslatorEnginePlugin() = default;

void TranslatorEnginePlugin::setInputText(const QString &text)
{
    d->mText = text;
}

void TranslatorEnginePlugin::setFrom(const QString &language)
{
    d->mFrom = language;
}

void TranslatorEnginePlugin::setTo(const QString &language)
{
    d->mTo = language;
}

QString TranslatorEnginePlugin::inputText() const
{
    return d->mText;
}

QString TranslatorEnginePlugin::from() const
{
    return d->mFrom;
}

QString TranslatorEnginePlugin::to() const
{
    return d->mTo;
}
