/*
  SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "pimcommontexttranslator_export.h"
#include <QString>
#include <memory>

namespace PimCommonTextTranslator
{
class TranslatorEnginePluginPrivate;
class PIMCOMMONTEXTTRANSLATOR_EXPORT TranslatorEnginePlugin
{
public:
    TranslatorEnginePlugin();
    virtual ~TranslatorEnginePlugin();

    virtual void translate() = 0;

    Q_REQUIRED_RESULT QString resultTranslate() const;
    void setInputText(const QString &text);
    void setFrom(const QString &language);
    void setTo(const QString &language);

    Q_REQUIRED_RESULT QString inputText() const;
    Q_REQUIRED_RESULT QString from() const;
    Q_REQUIRED_RESULT QString to() const;

private:
    std::unique_ptr<TranslatorEnginePluginPrivate> const d;
};
}
