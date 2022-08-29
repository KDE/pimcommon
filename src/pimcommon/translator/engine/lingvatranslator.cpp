/*
  SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
  Code based on Digikam donlinetranslator
*/

#include "lingvatranslator.h"
#include "pimcommon_debug.h"
#include "translator/translatorengineaccessmanager.h"
#include "translator/translatorutil.h"
#include <KLocalizedString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QNetworkAccessManager>

using namespace PimCommon;
LingvaTranslator::LingvaTranslator(QObject *parent)
    : TranslatorEngineBase{parent}
{
}

LingvaTranslator::~LingvaTranslator() = default;

QString PimCommon::LingvaTranslator::engineName() const
{
    return i18n("Lingva");
}

void LingvaTranslator::translate()
{
    if (mFrom == mTo) {
        Q_EMIT translateFailed(false, i18n("You used same language for from and to language."));
        return;
    }
    translateText();
}

QVector<QPair<QString, QString>> LingvaTranslator::supportedLanguage() const
{
    return {};
}

void LingvaTranslator::translateText()
{
    mResult.clear();

    const QUrl url(QString::fromUtf8("%1/api/v1/%2/%3/%4").arg(mServerUrl).arg(mFrom).arg(mTo).arg(QString::fromUtf8(QUrl::toPercentEncoding(mInputText))));

    const QNetworkRequest request(url);

    QNetworkReply *reply = TranslatorEngineAccessManager::self()->networkManager()->get(request);
    connect(reply, &QNetworkReply::errorOccurred, this, [this, reply](QNetworkReply::NetworkError error) {
        slotError(error);
        reply->deleteLater();
    });
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        reply->deleteLater();
        parseTranslation(reply);
    });
}

void LingvaTranslator::parseTranslation(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        Q_EMIT translateFailed(false, reply->errorString());
        reply->deleteLater();
        return;
    }

    const QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());
    const QJsonObject responseObject = jsonResponse.object();
    mResult = responseObject.value(QStringLiteral("translation")).toString();
    reply->deleteLater();
    Q_EMIT translateDone();
}
