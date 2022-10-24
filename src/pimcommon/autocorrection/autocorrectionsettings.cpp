/*
  SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "autocorrectionsettings.h"
#include "settings/pimcommonsettings.h"

using namespace PimCommon;
AutoCorrectionSettings::AutoCorrectionSettings()
{
    // default double quote open 0x201c
    // default double quote close 0x201d
    // default single quote open 0x2018
    // default single quote close 0x2019
    mTypographicSingleQuotes = AutoCorrectionUtils::typographicDefaultSingleQuotes();
    mTypographicDoubleQuotes = AutoCorrectionUtils::typographicDefaultDoubleQuotes();
}

AutoCorrectionSettings::~AutoCorrectionSettings() = default;

void AutoCorrectionSettings::setCapitalizeWeekDays(bool b)
{
    mCapitalizeWeekDays = b;
}

void AutoCorrectionSettings::setReplaceDoubleQuotes(bool b)
{
    mReplaceDoubleQuotes = b;
}

void AutoCorrectionSettings::setReplaceSingleQuotes(bool b)
{
    mReplaceSingleQuotes = b;
}

void AutoCorrectionSettings::setAdvancedAutocorrect(bool b)
{
    mAdvancedAutocorrect = b;
}

void AutoCorrectionSettings::setAutoFormatUrl(bool b)
{
    mAutoFormatUrl = b;
}

void AutoCorrectionSettings::setAutoBoldUnderline(bool b)
{
    mAutoBoldUnderline = b;
}

void AutoCorrectionSettings::setSuperScript(bool b)
{
    mSuperScriptAppendix = b;
}

void AutoCorrectionSettings::setAddNonBreakingSpace(bool b)
{
    mAddNonBreakingSpace = b;
}

bool AutoCorrectionSettings::isEnabledAutoCorrection() const
{
    return mEnabled;
}

bool AutoCorrectionSettings::isUppercaseFirstCharOfSentence() const
{
    return mUppercaseFirstCharOfSentence;
}

bool AutoCorrectionSettings::isFixTwoUppercaseChars() const
{
    return mFixTwoUppercaseChars;
}

bool AutoCorrectionSettings::isSingleSpaces() const
{
    return mSingleSpaces;
}

bool AutoCorrectionSettings::isAutoFractions() const
{
    return mAutoFractions;
}

bool AutoCorrectionSettings::isCapitalizeWeekDays() const
{
    return mCapitalizeWeekDays;
}

bool AutoCorrectionSettings::isReplaceDoubleQuotes() const
{
    return mReplaceDoubleQuotes;
}

bool AutoCorrectionSettings::isReplaceSingleQuotes() const
{
    return mReplaceSingleQuotes;
}

bool AutoCorrectionSettings::isAdvancedAutocorrect() const
{
    return mAdvancedAutocorrect;
}

bool AutoCorrectionSettings::isAutoFormatUrl() const
{
    return mAutoFormatUrl;
}

bool AutoCorrectionSettings::isAutoBoldUnderline() const
{
    return mAutoBoldUnderline;
}

bool AutoCorrectionSettings::isSuperScript() const
{
    return mSuperScriptAppendix;
}

bool AutoCorrectionSettings::isAddNonBreakingSpace() const
{
    return mAddNonBreakingSpace;
}

void AutoCorrectionSettings::setEnabledAutoCorrection(bool b)
{
    mEnabled = b;
}

PimCommon::AutoCorrectionUtils::TypographicQuotes AutoCorrectionSettings::typographicSingleQuotes() const
{
    return mTypographicSingleQuotes;
}

PimCommon::AutoCorrectionUtils::TypographicQuotes AutoCorrectionSettings::typographicDoubleQuotes() const
{
    return mTypographicDoubleQuotes;
}

void AutoCorrectionSettings::setTypographicSingleQuotes(PimCommon::AutoCorrectionUtils::TypographicQuotes singleQuote)
{
    mTypographicSingleQuotes = singleQuote;
}

void AutoCorrectionSettings::setTypographicDoubleQuotes(PimCommon::AutoCorrectionUtils::TypographicQuotes doubleQuote)
{
    mTypographicDoubleQuotes = doubleQuote;
}

void AutoCorrectionSettings::readConfig()
{
    mAutoBoldUnderline = PimCommon::PimCommonSettings::self()->autoBoldUnderline();
    mAutoFormatUrl = PimCommon::PimCommonSettings::self()->autoFormatUrl();
    mUppercaseFirstCharOfSentence = PimCommon::PimCommonSettings::self()->uppercaseFirstCharOfSentence();
    mFixTwoUppercaseChars = PimCommon::PimCommonSettings::self()->fixTwoUppercaseChars();
    mSingleSpaces = PimCommon::PimCommonSettings::self()->singleSpaces();
    mAutoFractions = PimCommon::PimCommonSettings::self()->autoFractions();
    mCapitalizeWeekDays = PimCommon::PimCommonSettings::self()->capitalizeWeekDays();
    mAdvancedAutocorrect = PimCommon::PimCommonSettings::self()->advancedAutocorrect();
    mReplaceDoubleQuotes = PimCommon::PimCommonSettings::self()->replaceDoubleQuotes();
    mReplaceSingleQuotes = PimCommon::PimCommonSettings::self()->replaceSingleQuotes();
    mEnabled = PimCommon::PimCommonSettings::self()->enabled();
    mSuperScriptAppendix = PimCommon::PimCommonSettings::self()->superScript();
    mAddNonBreakingSpace = PimCommon::PimCommonSettings::self()->addNonBreakingSpaceInFrench();
    // TODO readAutoCorrectionXmlFile();
}

void AutoCorrectionSettings::writeConfig()
{
    PimCommon::PimCommonSettings::self()->setAutoBoldUnderline(mAutoBoldUnderline);
    PimCommon::PimCommonSettings::self()->setAutoFormatUrl(mAutoFormatUrl);
    PimCommon::PimCommonSettings::self()->setUppercaseFirstCharOfSentence(mUppercaseFirstCharOfSentence);
    PimCommon::PimCommonSettings::self()->setFixTwoUppercaseChars(mFixTwoUppercaseChars);
    PimCommon::PimCommonSettings::self()->setSingleSpaces(mSingleSpaces);
    PimCommon::PimCommonSettings::self()->setAutoFractions(mAutoFractions);
    PimCommon::PimCommonSettings::self()->setCapitalizeWeekDays(mCapitalizeWeekDays);
    PimCommon::PimCommonSettings::self()->setAdvancedAutocorrect(mAdvancedAutocorrect);
    PimCommon::PimCommonSettings::self()->setReplaceDoubleQuotes(mReplaceDoubleQuotes);
    PimCommon::PimCommonSettings::self()->setReplaceSingleQuotes(mReplaceSingleQuotes);
    PimCommon::PimCommonSettings::self()->setEnabled(mEnabled);
    PimCommon::PimCommonSettings::self()->setSuperScript(mSuperScriptAppendix);
    PimCommon::PimCommonSettings::self()->setAddNonBreakingSpaceInFrench(mAddNonBreakingSpace);
    PimCommon::PimCommonSettings::self()->requestSync();
    // TODO writeAutoCorrectionXmlFile();
}

void AutoCorrectionSettings::setAutoFractions(bool newAutoFractions)
{
    mAutoFractions = newAutoFractions;
}

void AutoCorrectionSettings::setSingleSpaces(bool newSingleSpaces)
{
    mSingleSpaces = newSingleSpaces;
}

void AutoCorrectionSettings::setFixTwoUppercaseChars(bool newFixTwoUppercaseChars)
{
    mFixTwoUppercaseChars = newFixTwoUppercaseChars;
}

void AutoCorrectionSettings::setUppercaseFirstCharOfSentence(bool newUppercaseFirstCharOfSentence)
{
    mUppercaseFirstCharOfSentence = newUppercaseFirstCharOfSentence;
}

void AutoCorrectionSettings::setUpperCaseExceptions(const QSet<QString> &exceptions)
{
    mUpperCaseExceptions = exceptions;
}

void AutoCorrectionSettings::setTwoUpperLetterExceptions(const QSet<QString> &exceptions)
{
    mTwoUpperLetterExceptions = exceptions;
}

QSet<QString> AutoCorrectionSettings::upperCaseExceptions() const
{
    return mUpperCaseExceptions;
}

QSet<QString> AutoCorrectionSettings::twoUpperLetterExceptions() const
{
    return mTwoUpperLetterExceptions;
}

QString AutoCorrectionSettings::language() const
{
    return mAutoCorrectLang;
}

void AutoCorrectionSettings::setLanguage(const QString &lang, bool forceGlobal)
{
    if (mAutoCorrectLang != lang || forceGlobal) {
        mAutoCorrectLang = lang;
        // Re-read xml file
        // TODO readAutoCorrectionXmlFile(forceGlobal);
    }
}

bool AutoCorrectionSettings::isFrenchLanguage() const
{
    return mAutoCorrectLang == QLatin1String("FR_fr") || mAutoCorrectLang == QLatin1String("fr");
}

bool AutoCorrectionSettings::addAutoCorrect(const QString &currentWord, const QString &replaceWord)
{
    if (!mAutocorrectEntries.contains(currentWord)) {
        mAutocorrectEntries.insert(currentWord, replaceWord);
        // TODO writeAutoCorrectionXmlFile();
        return true;
    } else {
        return false;
    }
}

void AutoCorrectionSettings::setAutocorrectEntries(const QHash<QString, QString> &entries)
{
    // TODO
#if 0
    mMaxFindStringLength = 0;
    mMinFindStringLength = 0;
    QHashIterator<QString, QString> i(entries);
    while (i.hasNext()) {
        i.next();
        const int findStringLenght(i.key().length());
        mMaxFindStringLength = qMax(mMaxFindStringLength, findStringLenght);
        mMinFindStringLength = qMin(mMinFindStringLength, findStringLenght);
    }
    mAutocorrectEntries = entries;
#endif
}

QHash<QString, QString> AutoCorrectionSettings::autocorrectEntries() const
{
    return mAutocorrectEntries;
}
