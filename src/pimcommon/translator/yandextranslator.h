/*
  SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
  Code based on Digikam donlinetranslator
*/

#pragma once

#include "translatorenginebase.h"
namespace PimCommon
{
class YandexTranslator : public TranslatorEngineBase
{
    Q_OBJECT
public:
    explicit YandexTranslator(QObject *parent = nullptr);
    ~YandexTranslator() override;

    void translate() override;
    Q_REQUIRED_RESULT QMap<QString, QMap<QString, QString>> initListLanguage(QComboBox *from) override;

private:
    static QString sYandexKey;
    void parseCredentials(QNetworkReply *reply);
    void translateText();
};
}
