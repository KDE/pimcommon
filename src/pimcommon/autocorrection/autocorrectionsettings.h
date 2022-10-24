/*
  SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "autocorrectionutils.h"
#include "pimcommon_export.h"
#include <QObject>
#include <QSet>
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

    void setUpperCaseExceptions(const QSet<QString> &exceptions);
    void setTwoUpperLetterExceptions(const QSet<QString> &exceptions);
    Q_REQUIRED_RESULT QSet<QString> upperCaseExceptions() const;
    Q_REQUIRED_RESULT QSet<QString> twoUpperLetterExceptions() const;

    void setLanguage(const QString &lang, bool forceGlobal = false);
    Q_REQUIRED_RESULT QString language() const;

    Q_REQUIRED_RESULT bool isFrenchLanguage() const;
    void setAutocorrectEntries(const QHash<QString, QString> &entries);

    Q_REQUIRED_RESULT QHash<QString, QString> autocorrectEntries() const;
    Q_REQUIRED_RESULT bool addAutoCorrect(const QString &currentWord, const QString &replaceWord);

    Q_REQUIRED_RESULT QChar nonBreakingSpace() const;
    void setNonBreakingSpace(const QChar &newNonBreakingSpace);

    Q_REQUIRED_RESULT QHash<QString, QString> superScriptEntries() const;
    void setSuperScriptEntries(const QHash<QString, QString> &newSuperScriptEntries);

    void writeAutoCorrectionXmlFile(const QString &filename = QString());
    Q_REQUIRED_RESULT int maxFindStringLength() const;

    Q_REQUIRED_RESULT int minFindStringLength() const;

    void loadLocalFileName(const QString &localFileName, const QString &fname);
    void loadGlobalFileName(const QString &fname, bool forceGlobal);

private:
    void readAutoCorrectionXmlFile(bool forceGlobal = false);
    AutoCorrectionUtils::TypographicQuotes mTypographicSingleQuotes;
    AutoCorrectionUtils::TypographicQuotes mTypographicDoubleQuotes;

    QHash<QString, QString> mAutocorrectEntries;
    QHash<QString, QString> mSuperScriptEntries;

    QSet<QString> mUpperCaseExceptions;
    QSet<QString> mTwoUpperLetterExceptions;

    QString mAutoCorrectLang;

    QChar mNonBreakingSpace;

    int mMaxFindStringLength = 0;
    int mMinFindStringLength = 0;

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
