/*
  SPDX-FileCopyrightText: 2012-2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "translator/translatorenginebase.h"

#include <QNetworkReply>
#include <QObject>
class QNetworkAccessManager;
class QComboBox;

namespace PimCommon
{
class GoogleTranslator : public TranslatorEngineBase
{
    Q_OBJECT
public:
    explicit GoogleTranslator(QObject *parent = nullptr);
    ~GoogleTranslator() override;

    void translate() override;

    Q_REQUIRED_RESULT QString engineName() const override;
    Q_REQUIRED_RESULT QVector<QPair<QString, QString>> supportedLanguage() override;

protected:
    void loadSupportedLanguages() override;

private:
    void slotTranslateFinished(QNetworkReply *);
    static inline QVector<QPair<QString, QString>> mLanguages;
};
}
