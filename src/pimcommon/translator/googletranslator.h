/*
  SPDX-FileCopyrightText: 2012-2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "translatorenginebase.h"

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

    Q_REQUIRED_RESULT QMap<QString, QMap<QString, QString>> initListLanguage(QComboBox *from);
    void translate() override;

private Q_SLOTS:
    void slotTranslateFinished(QNetworkReply *);
    void slotError(QNetworkReply::NetworkError /*error*/);
};
}
