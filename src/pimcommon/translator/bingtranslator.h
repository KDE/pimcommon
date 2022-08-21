/*
  SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "translatorenginebase.h"
namespace PimCommon
{
class BingTranslator : public TranslatorEngineBase
{
    Q_OBJECT
public:
    explicit BingTranslator(QObject *parent = nullptr);
    ~BingTranslator() override;

    void translate() override;
    Q_REQUIRED_RESULT QMap<QString, QMap<QString, QString>> initListLanguage(QComboBox *from) override;

    static QByteArray sBingKey;
    static QByteArray sBingToken;
    static QString sBingIg;
    static QString sBingIid;

private:
    void parseCredentials(QNetworkReply *reply);
    void parseTranslation(QNetworkReply *reply);
    void translateText();
};
}
