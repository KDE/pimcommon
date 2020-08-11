/*
  SPDX-FileCopyrightText: 2012-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef AutoCorrection_H
#define AutoCorrection_H

#include "pimcommon_export.h"
#include <QTextCursor>
#include <QHash>
#include <QSet>

namespace PimCommon {
/**
 * @brief The AutoCorrection class
 * @author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT AutoCorrection
{
public:
    struct TypographicQuotes {
        QChar begin;
        QChar end;
    };

    explicit AutoCorrection();
    ~AutoCorrection();

    void setLanguage(const QString &lang, bool forceGlobal = false);
    void setEnabledAutoCorrection(bool b);
    void setUppercaseFirstCharOfSentence(bool b);
    void setFixTwoUppercaseChars(bool b);
    void setSingleSpaces(bool b);
    void setAutoFractions(bool b);
    void setCapitalizeWeekDays(bool b);
    void setReplaceDoubleQuotes(bool b);
    void setReplaceSingleQuotes(bool b);
    void setAdvancedAutocorrect(bool b);
    void setTypographicSingleQuotes(TypographicQuotes singleQuote);
    void setTypographicDoubleQuotes(TypographicQuotes doubleQuote);
    void setUpperCaseExceptions(const QSet<QString> &exceptions);
    void setTwoUpperLetterExceptions(const QSet<QString> &exceptions);
    void setAutocorrectEntries(const QHash<QString, QString> &entries);
    void setAutoFormatUrl(bool b);
    void setAutoBoldUnderline(bool b);
    void setSuperScript(bool b);
    void setAddNonBreakingSpace(bool b);

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

    Q_REQUIRED_RESULT QString language() const;
    Q_REQUIRED_RESULT TypographicQuotes typographicSingleQuotes() const;
    Q_REQUIRED_RESULT TypographicQuotes typographicDoubleQuotes() const;
    Q_REQUIRED_RESULT TypographicQuotes typographicDefaultSingleQuotes() const;
    Q_REQUIRED_RESULT TypographicQuotes typographicDefaultDoubleQuotes() const;
    Q_REQUIRED_RESULT QSet<QString> upperCaseExceptions() const;
    Q_REQUIRED_RESULT QSet<QString> twoUpperLetterExceptions() const;
    Q_REQUIRED_RESULT QHash<QString, QString> autocorrectEntries() const;

    bool autocorrect(bool htmlMode, QTextDocument &document, int &position);
    void writeConfig();

    Q_REQUIRED_RESULT bool addAutoCorrect(const QString &currentWord, const QString &replaceWord);

    void writeAutoCorrectionXmlFile(const QString &filename = QString());

    void setNonBreakingSpace(QChar nonBreakingSpace);

    void loadGlobalFileName(const QString &fname, bool forceGlobal);
    void loadLocalFileName(const QString &localFileName, const QString &fname);
private:
    bool isFrenchLanguage() const;
    void readConfig();

    void fixTwoUppercaseChars();
    bool singleSpaces();
    void capitalizeWeekDays();
    bool autoFractions();
    void uppercaseFirstCharOfSentence();
    int advancedAutocorrect();
    void replaceTypographicQuotes();
    void superscriptAppendix();
    void addNonBreakingSpace();

    void selectPreviousWord(QTextCursor &cursor, int cursorPosition);
    void selectStringOnMaximumSearchString(QTextCursor &cursor, int cursorPosition);

    bool autoFormatURLs();
    bool autoBoldUnderline();

    QString autoDetectURL(const QString &_word) const;
    void readAutoCorrectionXmlFile(bool forceGlobal = false);
    bool excludeToUppercase(const QString &word) const;
    QColor linkColor();

    bool mSingleSpaces; // suppress double spaces.
    bool mUppercaseFirstCharOfSentence; // convert first letter of a sentence automaticall to uppercase
    bool mFixTwoUppercaseChars;  // convert two uppercase characters to one upper and one lowercase.
    bool mAutoFractions; // replace 1/2 with ½
    bool mCapitalizeWeekDays;
    bool mAdvancedAutocorrect; // autocorrection from a list of entries

    bool mReplaceDoubleQuotes;  // replace double quotes with typographical quotes
    bool mReplaceSingleQuotes;  // replace single quotes with typographical quotes

    bool mAutoFormatUrl;
    bool mAutoBoldUnderline;
    bool mEnabled;
    bool mSuperScriptAppendix;

    bool mAddNonBreakingSpace;
    int mMaxFindStringLenght;
    int mMinFindStringLenght;
    QString mWord;
    QTextCursor mCursor;
    QChar mNonBreakingSpace;

    QString mAutoCorrectLang;
    QStringList mCacheNameOfDays;
    QSet<QString> mUpperCaseExceptions;
    QSet<QString> mTwoUpperLetterExceptions;
    QHash<QString, QString> mAutocorrectEntries;
    QHash<QString, QString> mSuperScriptEntries;
    TypographicQuotes mTypographicSingleQuotes;
    TypographicQuotes mTypographicDoubleQuotes;
    QColor mLinkColor;
};
}

#endif // AutoCorrection_H
