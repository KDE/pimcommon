/*
  SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "translatorenginebase.h"
#include "translatordebugdialog.h"
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
