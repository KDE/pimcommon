/*
  SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "translatorenginebase.h"
#include "translatordebugdialog.h"
#include <KLocalizedString>

using namespace PimCommon;
TranslatorEngineBase::TranslatorEngineBase(QObject *parent)
    : QObject{parent}
{
    mDebug = !qEnvironmentVariableIsEmpty("KDEPIM_DEBUGGING");
}

TranslatorEngineBase::~TranslatorEngineBase()
{
}

void TranslatorEngineBase::setParentWidget(QWidget *parent)
{
    mParentWidget = parent;
}

void TranslatorEngineBase::setInputText(const QString &text)
{
    mInputText = text;
}

void TranslatorEngineBase::setFrom(const QString &language)
{
    mFrom = language;
}

void TranslatorEngineBase::setTo(const QString &language)
{
    mTo = language;
}

QString TranslatorEngineBase::resultTranslate() const
{
    return mResult;
}

void TranslatorEngineBase::debug()
{
    if (mDebug) {
        TranslatorDebugDialog dlg(mParentWidget);
        dlg.setDebug(mJsonDebug);
        dlg.exec();
    }
}

void TranslatorEngineBase::clear()
{
    mJsonData.clear();
}

void TranslatorEngineBase::slotError(QNetworkReply::NetworkError error)
{
    QString messageError;
    if (error == QNetworkReply::ServiceUnavailableError) {
        messageError = i18n("Error: Engine systems have detected suspicious traffic from your computer network. Please try your request again later.");
    }
    Q_EMIT translateFailed(false, messageError);
}
