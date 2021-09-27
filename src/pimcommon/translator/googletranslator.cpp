/*
  SPDX-FileCopyrightText: 2012-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "googletranslator.h"
#include "pimcommon_debug.h"
#include "translatordebugdialog.h"
#include "translatorutil.h"
#include <KLocalizedString>
#include <QJsonParseError>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QPointer>
#include <QUrlQuery>

using namespace PimCommon;

GoogleTranslator::GoogleTranslator(QObject *parent)
    : QObject(parent)
    , mNetworkAccessManager(new QNetworkAccessManager(this))
{
    mNetworkAccessManager->setRedirectPolicy(QNetworkRequest::NoLessSafeRedirectPolicy);
    mNetworkAccessManager->setStrictTransportSecurityEnabled(true);
    mNetworkAccessManager->enableStrictTransportSecurityStore(true);
    mDebug = !qEnvironmentVariableIsEmpty("KDEPIM_DEBUGGING");
    connect(mNetworkAccessManager, &QNetworkAccessManager::finished, this, &GoogleTranslator::slotTranslateFinished);
}

GoogleTranslator::~GoogleTranslator()
{
}

void GoogleTranslator::setParentWidget(QWidget *parent)
{
    mParentWidget = parent;
}

void GoogleTranslator::setInputText(const QString &text)
{
    mInputText = text;
}

void GoogleTranslator::setFrom(const QString &language)
{
    mFrom = language;
}

void GoogleTranslator::setTo(const QString &language)
{
    mTo = language;
}

QString GoogleTranslator::resultTranslate() const
{
    return mResult;
}

QMap<QString, QMap<QString, QString>> GoogleTranslator::initListLanguage(QComboBox *from)
{
    QMap<QString, QMap<QString, QString>> listLanguage;

    TranslatorUtil translatorUtil;
    QVector<QPair<QString, QString>> fullListLanguage;
    fullListLanguage.append(translatorUtil.pair(TranslatorUtil::automatic));
    fullListLanguage.append(translatorUtil.pair(TranslatorUtil::en));
    fullListLanguage.append(translatorUtil.pair(TranslatorUtil::nl));
    fullListLanguage.append(translatorUtil.pair(TranslatorUtil::fr));
    fullListLanguage.append(translatorUtil.pair(TranslatorUtil::de));
    fullListLanguage.append(translatorUtil.pair(TranslatorUtil::el));
    fullListLanguage.append(translatorUtil.pair(TranslatorUtil::it));
    fullListLanguage.append(translatorUtil.pair(TranslatorUtil::ja));
    fullListLanguage.append(translatorUtil.pair(TranslatorUtil::ko));
    fullListLanguage.append(translatorUtil.pair(TranslatorUtil::pt));
    fullListLanguage.append(translatorUtil.pair(TranslatorUtil::ru));
    fullListLanguage.append(translatorUtil.pair(TranslatorUtil::es));

    fullListLanguage.append(translatorUtil.pair(TranslatorUtil::af));
    fullListLanguage.append(translatorUtil.pair(TranslatorUtil::sq));
    fullListLanguage.append(translatorUtil.pair(TranslatorUtil::ar));
    fullListLanguage.append(translatorUtil.pair(TranslatorUtil::hy));
    fullListLanguage.append(translatorUtil.pair(TranslatorUtil::az));
    fullListLanguage.append(translatorUtil.pair(TranslatorUtil::eu));
    fullListLanguage.append(translatorUtil.pair(TranslatorUtil::be));
    fullListLanguage.append(translatorUtil.pair(TranslatorUtil::bg));
    fullListLanguage.append(translatorUtil.pair(TranslatorUtil::ca));
    fullListLanguage.append(translatorUtil.pair(TranslatorUtil::zh_cn_google)); // For google only
    fullListLanguage.append(translatorUtil.pair(TranslatorUtil::zh_tw_google)); // For google only
    fullListLanguage.append(translatorUtil.pair(TranslatorUtil::hr));
    fullListLanguage.append(translatorUtil.pair(TranslatorUtil::cs));
    fullListLanguage.append(translatorUtil.pair(TranslatorUtil::da));
    fullListLanguage.append(translatorUtil.pair(TranslatorUtil::et));
    fullListLanguage.append(translatorUtil.pair(TranslatorUtil::tl));
    fullListLanguage.append(translatorUtil.pair(TranslatorUtil::fi));
    fullListLanguage.append(translatorUtil.pair(TranslatorUtil::gl));
    fullListLanguage.append(translatorUtil.pair(TranslatorUtil::ka));
    fullListLanguage.append(translatorUtil.pair(TranslatorUtil::ht));
    fullListLanguage.append(translatorUtil.pair(TranslatorUtil::iw));
    fullListLanguage.append(translatorUtil.pair(TranslatorUtil::hi));
    fullListLanguage.append(translatorUtil.pair(TranslatorUtil::hu));
    fullListLanguage.append(translatorUtil.pair(TranslatorUtil::is));
    fullListLanguage.append(translatorUtil.pair(TranslatorUtil::id));
    fullListLanguage.append(translatorUtil.pair(TranslatorUtil::ga));
    fullListLanguage.append(translatorUtil.pair(TranslatorUtil::lv));
    fullListLanguage.append(translatorUtil.pair(TranslatorUtil::lt));
    fullListLanguage.append(translatorUtil.pair(TranslatorUtil::mk));
    fullListLanguage.append(translatorUtil.pair(TranslatorUtil::ms));
    fullListLanguage.append(translatorUtil.pair(TranslatorUtil::mt));
    fullListLanguage.append(translatorUtil.pair(TranslatorUtil::no));
    fullListLanguage.append(translatorUtil.pair(TranslatorUtil::fa));
    fullListLanguage.append(translatorUtil.pair(TranslatorUtil::pl));
    fullListLanguage.append(translatorUtil.pair(TranslatorUtil::ro));
    fullListLanguage.append(translatorUtil.pair(TranslatorUtil::sr));
    fullListLanguage.append(translatorUtil.pair(TranslatorUtil::sk));
    fullListLanguage.append(translatorUtil.pair(TranslatorUtil::sl));
    fullListLanguage.append(translatorUtil.pair(TranslatorUtil::sw));
    fullListLanguage.append(translatorUtil.pair(TranslatorUtil::sv));
    fullListLanguage.append(translatorUtil.pair(TranslatorUtil::th));
    fullListLanguage.append(translatorUtil.pair(TranslatorUtil::tr));
    fullListLanguage.append(translatorUtil.pair(TranslatorUtil::uk));
    fullListLanguage.append(translatorUtil.pair(TranslatorUtil::ur));
    fullListLanguage.append(translatorUtil.pair(TranslatorUtil::vi));
    fullListLanguage.append(translatorUtil.pair(TranslatorUtil::cy));
    fullListLanguage.append(translatorUtil.pair(TranslatorUtil::yi));
    const int fullListLanguageSize(fullListLanguage.count());
    for (int i = 0; i < fullListLanguageSize; ++i) {
        const QPair<QString, QString> currentLanguage = fullListLanguage.at(i);
        translatorUtil.addItemToFromComboBox(from, currentLanguage);

        QMap<QString, QString> toList;
        for (int j = 0; j < fullListLanguageSize; ++j) {
            if (j != 0 && j != i) { // don't add auto and current language
                translatorUtil.addPairToMap(toList, fullListLanguage.at(j));
            }
        }
        listLanguage.insert(currentLanguage.second, toList);
    }

    return listLanguage;
}

void GoogleTranslator::translate()
{
    if (mFrom == mTo) {
        Q_EMIT translateFailed(false, i18n("You used same language for from and to language."));
        return;
    }

    mResult.clear();

    QUrlQuery urlQuery;
    urlQuery.addQueryItem(QStringLiteral("client"), QStringLiteral("gtx"));
    urlQuery.addQueryItem(QStringLiteral("sl"), mFrom);
    urlQuery.addQueryItem(QStringLiteral("tl"), mTo);
    urlQuery.addQueryItem(QStringLiteral("dt"), QStringLiteral("t"));
    urlQuery.addQueryItem(QStringLiteral("q"), mInputText);

    QUrl url;
    url.setQuery(urlQuery);
    url.setScheme(QStringLiteral("https"));
    url.setHost(QStringLiteral("translate.googleapis.com"));
    url.setPath(QStringLiteral("/translate_a/single"));
    const QNetworkRequest request(url);

    QNetworkReply *reply = mNetworkAccessManager->get(request);
    connect(reply, &QNetworkReply::errorOccurred, this, &GoogleTranslator::slotError);
}

void GoogleTranslator::slotError(QNetworkReply::NetworkError /*error*/)
{
    Q_EMIT translateFailed(false);
}

void GoogleTranslator::slotTranslateFinished(QNetworkReply *reply)
{
    mResult.clear();
    mJsonData = QString::fromUtf8(reply->readAll());
    reply->deleteLater();
    //  jsonData contains arrays like this: ["foo",,"bar"]
    //  but this is not valid JSON for QJSON, it expects empty strings: ["foo","","bar"]
    mJsonData.replace(QRegExp(QLatin1String(",{3,3}")), QStringLiteral(",\"\",\"\","));
    mJsonData.replace(QRegExp(QLatin1String(",{2,2}")), QStringLiteral(",\"\","));
    // qCDebug(PIMCOMMON_LOG) << mJsonData;

    QJsonParseError parsingError;
    const QJsonDocument jsonDoc = QJsonDocument::fromJson(mJsonData.toUtf8(), &parsingError);
    if (parsingError.error != QJsonParseError::NoError || jsonDoc.isNull()) {
        Q_EMIT translateFailed(false);
        return;
    }
    const QVariantList json = jsonDoc.toVariant().toList();
    if (mDebug) {
        mJsonDebug = QString::fromUtf8(jsonDoc.toJson(QJsonDocument::Indented));
    }
    for (const QVariant &level0 : json) {
        const QVariantList listLevel0 = level0.toList();
        if (listLevel0.isEmpty()) {
            continue;
        }
        for (const QVariant &level1 : listLevel0) {
            if (level1.toList().size() <= 2) {
                continue;
            }
            mResult += level1.toList().at(0).toString();
        }
    }
    Q_EMIT translateDone();
}

void GoogleTranslator::debug()
{
    if (mDebug) {
        QPointer<TranslatorDebugDialog> dlg = new TranslatorDebugDialog(mParentWidget);
        dlg->setDebug(mJsonDebug);
        dlg->exec();
        delete dlg;
    }
}

void GoogleTranslator::clear()
{
    mJsonData.clear();
}
