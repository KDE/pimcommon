/*
  SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

#include "pimcommontexttranslator_export.h"
namespace PimCommonTextTranslator
{
class TranslatorEnginePlugin;
class PIMCOMMONTEXTTRANSLATOR_EXPORT TranslatorEngineClient : public QObject
{
    Q_OBJECT
public:
    explicit TranslatorEngineClient(QObject *parent = nullptr);
    ~TranslatorEngineClient() override;

    /**
     * @returns the name of the implementing class.
     */
    virtual QString name() const = 0;

    virtual TranslatorEnginePlugin *createSpeller(const QString &language) = 0;
};
}
