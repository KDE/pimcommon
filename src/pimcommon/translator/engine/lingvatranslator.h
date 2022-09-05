/*
  SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
  Code based on Digikam donlinetranslator
*/

#pragma once

#include "translator/translatorenginebase.h"
namespace PimCommon
{
class LingvaTranslator : public TranslatorEngineBase
{
    Q_OBJECT
public:
    explicit LingvaTranslator(QObject *parent = nullptr);
    ~LingvaTranslator() override;

    Q_REQUIRED_RESULT QString engineName() const override;
    void translate() override;
    Q_REQUIRED_RESULT QVector<QPair<QString, QString>> supportedLanguage() override;
    void loadSettings() override;

protected:
    void loadSupportedLanguages() override;

private:
    void translateText();
    void parseTranslation(QNetworkReply *reply);
};
}
