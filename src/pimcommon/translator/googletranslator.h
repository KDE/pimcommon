/*
  SPDX-FileCopyrightText: 2012-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef GOOGLETRANSLATOR_H
#define GOOGLETRANSLATOR_H

#include <QNetworkReply>
#include <QObject>
class QNetworkAccessManager;
class QComboBox;
class QNetworkReply;

namespace PimCommon
{
class GoogleTranslator : public QObject
{
    Q_OBJECT
public:
    explicit GoogleTranslator(QObject *parent = nullptr);
    ~GoogleTranslator() override;

    void setParentWidget(QWidget *parent);

    Q_REQUIRED_RESULT QMap<QString, QMap<QString, QString>> initListLanguage(QComboBox *from);
    void translate();
    void debug();
    void clear();

    Q_REQUIRED_RESULT QString resultTranslate() const;
    void setInputText(const QString &text);
    void setFrom(const QString &language);
    void setTo(const QString &language);

private Q_SLOTS:
    void slotTranslateFinished(QNetworkReply *);
    void slotError(QNetworkReply::NetworkError /*error*/);

Q_SIGNALS:
    void translateDone();
    void translateFailed(bool result, const QString &errorMessage = QString());

private:
    QString mInputText;
    QString mFrom;
    QString mTo;
    QString mResult;
    QString mJsonData;
    QString mJsonDebug;
    QNetworkAccessManager *const mNetworkAccessManager;
    QWidget *mParentWidget = nullptr;
    bool mDebug = false;
};
}

#endif // GOOGLETRANSLATOR_H
