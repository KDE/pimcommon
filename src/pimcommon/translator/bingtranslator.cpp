/*
  SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
  Code based on Digikam donlinetranslator
*/

#include "bingtranslator.h"
#include "translatorengineaccessmanager.h"

#include <KLocalizedString>

#include <QNetworkReply>
#include <QUrlQuery>
using namespace PimCommon;

QByteArray BingTranslator::sBingKey;
QByteArray BingTranslator::sBingToken;
QString BingTranslator::sBingIg;
QString BingTranslator::sBingIid;

BingTranslator::BingTranslator(QObject *parent)
    : TranslatorEngineBase{parent}
{
}

BingTranslator::~BingTranslator() = default;

void BingTranslator::translate()
{
    if (sBingKey.isEmpty() || sBingToken.isEmpty()) {
        const QUrl url(QStringLiteral("https://www.bing.com/translator"));
        QNetworkReply *reply = TranslatorEngineAccessManager::self()->networkManager()->get(QNetworkRequest(url));
        connect(reply, &QNetworkReply::finished, this, [this, reply]() {
            reply->deleteLater();
            parseCredentials(reply);
        });
        connect(reply, &QNetworkReply::errorOccurred, this, [this, reply](QNetworkReply::NetworkError error) {
            slotError(error);
            reply->deleteLater();
        });
    } else {
        translateText();
    }
}

void BingTranslator::parseCredentials(QNetworkReply *reply)
{
    const QByteArray webSiteData = reply->readAll();
    const QByteArray credentialsBeginString = QByteArrayLiteral("var params_RichTranslateHelper = [");
    const int credentialsBeginPos = webSiteData.indexOf(credentialsBeginString);

    if (credentialsBeginPos == -1) {
        translateFailed(false, i18n("Error: Unable to find Bing credentials in web version."));
        reply->deleteLater();
        return;
    }

    const int keyBeginPos = credentialsBeginPos + credentialsBeginString.size();
    const int keyEndPos = webSiteData.indexOf(',', keyBeginPos);

    if (keyEndPos == -1) {
        translateFailed(false, i18n("Error: Unable to extract Bing key from web version."));
        reply->deleteLater();
        return;
    }

    sBingKey = webSiteData.mid(keyBeginPos, keyEndPos - keyBeginPos);
    const int tokenBeginPos = keyEndPos + 2; // Skip two symbols instead of one because the value is enclosed in quotes
    const int tokenEndPos = webSiteData.indexOf('"', tokenBeginPos);

    if (tokenEndPos == -1) {
        translateFailed(false, i18n("Error: Unable to extract Bing token from web version."));
        reply->deleteLater();
        return;
    }

    sBingToken = webSiteData.mid(tokenBeginPos, tokenEndPos - tokenBeginPos);
    const int igBeginPos = webSiteData.indexOf("IG");
    const int igEndPos = webSiteData.indexOf('"', igBeginPos + 2);

    if (igEndPos == -1) {
        translateFailed(false, i18n("Error: Unable to extract additional Bing information from web version."));
        reply->deleteLater();
        return;
    }

    sBingIg = QString::fromUtf8(webSiteData.mid(igBeginPos, igEndPos - igBeginPos));
    const int iidBeginPos = webSiteData.indexOf("data-iid");
    const int iidEndPos = webSiteData.indexOf('"', iidBeginPos + 2);

    if (iidEndPos == -1) {
        translateFailed(false, i18n("Error: Unable to extract additional Bing information from web version."));
        reply->deleteLater();
        return;
    }

    sBingIid = QString::fromUtf8(webSiteData.mid(iidBeginPos, iidEndPos - iidBeginPos));
    reply->deleteLater();
    translateText();
}

void BingTranslator::translateText()
{
    if (mFrom == mTo) {
        Q_EMIT translateFailed(false, i18n("You used same language for from and to language."));
        return;
    }

    mResult.clear();

#if 0
    const QByteArray postData = "&text="     + QUrl::toPercentEncoding(sourceText)
                              + "&fromLang=" + languageApiCode(Bing, m_sourceLang).toUtf8()
                              + "&to="       + languageApiCode(Bing, m_translationLang).toUtf8()
                              + "&token="    + s_bingToken
                              + "&key="      + s_bingKey;

    QUrl url(QStringLiteral("https://www.bing.com/ttranslatev3"));
    url.setQuery(QStringLiteral("IG=%1&IID=%2").arg(s_bingIg, s_bingIid));

    // Setup request

    QNetworkRequest request;
    request.setHeader(QNetworkRequest::ContentTypeHeader, QLatin1String("application/x-www-form-urlencoded"));
    request.setHeader(QNetworkRequest::UserAgentHeader, QString::fromUtf8("%1/%2").arg(QCoreApplication::applicationName()).arg(QCoreApplication::applicationVersion()));
    request.setUrl(url);

    // Make reply

    m_currentReply = m_networkManager->post(request, postData);

#endif

    QUrlQuery urlQuery;
    urlQuery.addQueryItem(QStringLiteral("IG"), sBingIg);
    urlQuery.addQueryItem(QStringLiteral("IDD"), sBingIid);
    QUrl url(QStringLiteral("https://www.bing.com/ttranslatev3"));
    url.setQuery(urlQuery);

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, QLatin1String("application/x-www-form-urlencoded"));
    // request.setHeader(QNetworkRequest::UserAgentHeader,
    // QString::fromUtf8("%1/%2").arg(QCoreApplication::applicationName()).arg(QCoreApplication::applicationVersion()));

    QNetworkReply *reply = TranslatorEngineAccessManager::self()->networkManager()->get(request);
    connect(reply, &QNetworkReply::errorOccurred, this, [this, reply](QNetworkReply::NetworkError error) {
        slotError(error);
        reply->deleteLater();
    });

    // TODO
}