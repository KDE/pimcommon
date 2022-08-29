/*
  SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "pimcommon_export.h"
#include <QNetworkReply>
#include <QObject>
namespace PimCommon
{
class PIMCOMMON_EXPORT TranslatorEngineBase : public QObject
{
    Q_OBJECT
public:
    enum TranslatorEngine {
        Google = 0,
        Bing = 1,
        Yandex = 2,
        Lingva = 3,
        LibreTranslate = 4,
        LastEngine = LibreTranslate,
    };

    Q_REQUIRED_RESULT virtual QString engineName() const = 0;

    virtual void translate() = 0;
    Q_REQUIRED_RESULT virtual QVector<QPair<QString, QString>> supportedLanguage() const = 0;

    explicit TranslatorEngineBase(QObject *parent = nullptr);
    ~TranslatorEngineBase() override;

    Q_REQUIRED_RESULT QString resultTranslate() const;
    void setInputText(const QString &text);
    void setFrom(const QString &language);
    void setTo(const QString &language);

    void clear();

    Q_REQUIRED_RESULT QString jsonDebug() const;

    void setServerUrl(const QString &newServerUrl);

Q_SIGNALS:
    void translateDone();
    void translateFailed(bool result, const QString &errorMessage = QString());

protected:
    QString mJsonData;
    QString mJsonDebug;
    QString mInputText;
    QString mFrom;
    QString mTo;
    QString mResult;

    QString mServerUrl;

    bool mDebug = false;

    void slotError(QNetworkReply::NetworkError error);
};
}
