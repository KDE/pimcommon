/*
  SPDX-FileCopyrightText: 2012-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "importabstractautocorrection.h"

using namespace PimCommon;

ImportAbstractAutocorrection::ImportAbstractAutocorrection(QWidget *parent)
    : mParent(parent)
{
}

ImportAbstractAutocorrection::~ImportAbstractAutocorrection()
{
}

QSet<QString> ImportAbstractAutocorrection::upperCaseExceptions() const
{
    return mUpperCaseExceptions;
}

QSet<QString> ImportAbstractAutocorrection::twoUpperLetterExceptions() const
{
    return mTwoUpperLetterExceptions;
}

QHash<QString, QString> ImportAbstractAutocorrection::autocorrectEntries() const
{
    return mAutocorrectEntries;
}

AutoCorrection::TypographicQuotes ImportAbstractAutocorrection::typographicSingleQuotes() const
{
    return mTypographicSingleQuotes;
}

AutoCorrection::TypographicQuotes ImportAbstractAutocorrection::typographicDoubleQuotes() const
{
    return mTypographicDoubleQuotes;
}

int ImportAbstractAutocorrection::maxFindStringLenght() const
{
    return mMaxFindStringLenght;
}

int ImportAbstractAutocorrection::minFindStringLenght() const
{
    return mMinFindStringLenght;
}

QHash<QString, QString> ImportAbstractAutocorrection::superScriptEntries() const
{
    return mSuperScriptEntries;
}
