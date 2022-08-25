/*
  SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
  Code based on Digikam donlinetranslator
*/

#pragma once

#include "translator/translatorenginebase.h"
namespace PimCommon
{
class YandexTranslator : public TranslatorEngineBase
{
    Q_OBJECT
public:
    explicit YandexTranslator(QObject *parent = nullptr);
    ~YandexTranslator() override;

    void translate() override;
    Q_REQUIRED_RESULT QVector<QPair<QString, QString>> supportedLanguage() const override;

private:
    static QString sYandexKey;
    void parseCredentials(QNetworkReply *reply);
    void parseTranslation(QNetworkReply *reply);
    void translateText();
};
}
