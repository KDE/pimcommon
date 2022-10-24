/*
  SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "autocorrectionutils.h"
#include "pimcommon_export.h"
#include <QObject>
namespace PimCommon
{
class PIMCOMMON_EXPORT AutoCorrectionSettings
{
public:
    AutoCorrectionSettings();
    ~AutoCorrectionSettings();

    Q_REQUIRED_RESULT bool isEnabledAutoCorrection() const;
    Q_REQUIRED_RESULT bool isUppercaseFirstCharOfSentence() const;
    Q_REQUIRED_RESULT bool isFixTwoUppercaseChars() const;
    Q_REQUIRED_RESULT bool isSingleSpaces() const;
    Q_REQUIRED_RESULT bool isAutoFractions() const;
    Q_REQUIRED_RESULT bool isCapitalizeWeekDays() const;
    Q_REQUIRED_RESULT bool isReplaceDoubleQuotes() const;
    Q_REQUIRED_RESULT bool isReplaceSingleQuotes() const;
    Q_REQUIRED_RESULT bool isAdvancedAutocorrect() const;
    Q_REQUIRED_RESULT bool isAutoFormatUrl() const;
    Q_REQUIRED_RESULT bool isAutoBoldUnderline() const;
    Q_REQUIRED_RESULT bool isSuperScript() const;

    Q_REQUIRED_RESULT bool isAddNonBreakingSpace() const;

    Q_REQUIRED_RESULT PimCommon::AutoCorrectionUtils::TypographicQuotes typographicSingleQuotes() const;
    Q_REQUIRED_RESULT PimCommon::AutoCorrectionUtils::TypographicQuotes typographicDoubleQuotes() const;
    void setTypographicSingleQuotes(PimCommon::AutoCorrectionUtils::TypographicQuotes singleQuote);
    void setTypographicDoubleQuotes(PimCommon::AutoCorrectionUtils::TypographicQuotes doubleQuote);

    void setAutoFormatUrl(bool b);
    void setAutoBoldUnderline(bool b);
    void setSuperScript(bool b);
    void setAddNonBreakingSpace(bool b);
    void setCapitalizeWeekDays(bool b);
    void setReplaceDoubleQuotes(bool b);
    void setReplaceSingleQuotes(bool b);
    void setAdvancedAutocorrect(bool b);
    void setEnabledAutoCorrection(bool b);

    void readConfig();

    void writeConfig();

    void setAutoFractions(bool newAutoFractions);

    void setSingleSpaces(bool newSingleSpaces);

    void setFixTwoUppercaseChars(bool newFixTwoUppercaseChars);

    void setUppercaseFirstCharOfSentence(bool newUppercaseFirstCharOfSentence);

private:
    AutoCorrectionUtils::TypographicQuotes mTypographicSingleQuotes;
    AutoCorrectionUtils::TypographicQuotes mTypographicDoubleQuotes;

    bool mSingleSpaces = true; // suppress double spaces.
    bool mUppercaseFirstCharOfSentence = false; // convert first letter of a sentence automatically to uppercase
    bool mFixTwoUppercaseChars = false; // convert two uppercase characters to one upper and one lowercase.
    bool mAutoFractions = true; // replace 1/2 with ½
    bool mCapitalizeWeekDays = false;
    bool mAdvancedAutocorrect = false; // autocorrection from a list of entries

    bool mReplaceDoubleQuotes = false; // replace double quotes with typographical quotes
    bool mReplaceSingleQuotes = false; // replace single quotes with typographical quotes

    bool mAutoFormatUrl = false;
    bool mAutoBoldUnderline = false;
    bool mEnabled = false;
    bool mSuperScriptAppendix = false;

    bool mAddNonBreakingSpace = false;
};
}
