/*
  SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
  Code based on Digikam donlinetranslator
*/

#include "yandextranslator.h"
#include "translator/translatorengineaccessmanager.h"
#include <KLocalizedString>

using namespace PimCommon;
QString YandexTranslator::sYandexKey;
YandexTranslator::YandexTranslator(QObject *parent)
    : TranslatorEngineBase{parent}
{
}

YandexTranslator::~YandexTranslator() = default;

void YandexTranslator::translate()
{
    if (sYandexKey.isEmpty()) {
        const QUrl url(QStringLiteral("https://translate.yandex.com"));

        QNetworkReply *reply = TranslatorEngineAccessManager::self()->networkManager()->get(QNetworkRequest(url));
        connect(reply, &QNetworkReply::finished, this, [this, reply]() {
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

QMap<QString, QMap<QString, QString>> YandexTranslator::initListLanguage(QComboBox *from)
{
    return {};
}

void YandexTranslator::parseCredentials(QNetworkReply *reply)
{
    // Check availability of service
    const QByteArray webSiteData = reply->readAll();
    reply->deleteLater();
    if (webSiteData.isEmpty() || webSiteData.contains("<title>Oops!</title>") || webSiteData.contains("<title>302 Found</title>")) {
        Q_EMIT translateFailed(false,
                               i18n("Error: Engine systems have detected suspicious traffic "
                                    "from your computer network. Please try your request again later."));
        return;
    }

    const QByteArray sidBeginString = "SID: '";
    const int sidBeginStringPos = webSiteData.indexOf(sidBeginString);

    if (sidBeginStringPos == -1) {
        Q_EMIT translateFailed(false, i18n("Error: Unable to find Yandex SID in web version."));
        return;
    }

    const int sidBeginPosition = sidBeginStringPos + sidBeginString.size();
    const int sidEndPosition = webSiteData.indexOf('\'', sidBeginPosition);

    if (sidEndPosition == -1) {
        Q_EMIT translateFailed(false, i18n("Error: Unable to extract Yandex SID from web version."));
        return;
    }

    // Yandex show reversed parts of session ID, need to decode

    const QString sid = QString::fromUtf8(webSiteData.mid(sidBeginPosition, sidEndPosition - sidBeginPosition));

    QStringList sidParts = sid.split(QLatin1Char('.'));

    for (int i = 0; i < sidParts.size(); ++i) {
        std::reverse(sidParts[i].begin(), sidParts[i].end());
    }

    sYandexKey = sidParts.join(QLatin1Char('.'));
    translateText();
}

void YandexTranslator::translateText()
{
    if (mFrom == mTo) {
        Q_EMIT translateFailed(false, i18n("You used same language for from and to language."));
        return;
    }

    mResult.clear();
#if 0
    const QString sourceText = sender()->property(s_textProperty).toString();

    QString lang;

    if (m_sourceLang == Auto)
    {
        lang = languageApiCode(Yandex, m_translationLang);
    }
    else
    {
        lang = languageApiCode(Yandex, m_sourceLang) + QLatin1Char('-') + languageApiCode(Yandex, m_translationLang);
    }

    // Generate API url

    QUrl url(QStringLiteral("https://translate.yandex.net/api/v1/tr.json/translate"));

    url.setQuery(QStringLiteral("id=%1-2-0&srv=tr-text&text=%2&lang=%3")
                     .arg(s_yandexKey,
                          QString::fromUtf8(QUrl::toPercentEncoding(sourceText)),
                          lang));

    // Setup request

    QNetworkRequest request;
    request.setHeader(QNetworkRequest::ContentTypeHeader, QLatin1String("application/x-www-form-urlencoded"));
    request.setUrl(url);

    // Make reply

    m_currentReply = m_networkManager->post(request, QByteArray());

#endif
    // TODO
}

void YandexTranslator::parseTranslation(QNetworkReply *reply)
{
    // TODO
    reply->deleteLater();
    Q_EMIT translateDone();
}
