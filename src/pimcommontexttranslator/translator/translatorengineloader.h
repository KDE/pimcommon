/*
  SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "pimcommontexttranslator_export.h"
#include <QObject>
#include <memory>
namespace PimCommonTextTranslator
{
class TranslatorEngineLoaderPrivate;
class TranslatorEnginePlugin;
class PIMCOMMONTEXTTRANSLATOR_EXPORT TranslatorEngineLoader : public QObject
{
    Q_OBJECT
public:
    explicit TranslatorEngineLoader(QObject *parent = nullptr);
    ~TranslatorEngineLoader() override;

    Q_REQUIRED_RESULT TranslatorEnginePlugin *createTranslator(const QString &clientName) const;

private:
    void loadPlugins();
    void loadPlugin(const QString &pluginPath);

private:
    std::unique_ptr<TranslatorEngineLoaderPrivate> const d;
};
}
