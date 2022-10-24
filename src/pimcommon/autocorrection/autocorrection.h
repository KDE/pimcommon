/*
  SPDX-FileCopyrightText: 2012-2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "autocorrectionsettings.h"
#include "autocorrectionutils.h"
#include "pimcommon_export.h"
#include <QHash>
#include <QSet>
#include <QTextCursor>

namespace PimCommon
{
/**
 * @brief The AutoCorrection class
 * @author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT AutoCorrection
{
public:
    explicit AutoCorrection();
    ~AutoCorrection();

    void setLanguage(const QString &lang, bool forceGlobal = false);
    void setTypographicSingleQuotes(AutoCorrectionUtils::TypographicQuotes singleQuote);
    void setTypographicDoubleQuotes(AutoCorrectionUtils::TypographicQuotes doubleQuote);
    void setUpperCaseExceptions(const QSet<QString> &exceptions);
    void setTwoUpperLetterExceptions(const QSet<QString> &exceptions);
    void setAutocorrectEntries(const QHash<QString, QString> &entries);

    Q_REQUIRED_RESULT QString language() const;
    Q_REQUIRED_RESULT AutoCorrectionUtils::TypographicQuotes typographicSingleQuotes() const;
    Q_REQUIRED_RESULT AutoCorrectionUtils::TypographicQuotes typographicDoubleQuotes() const;
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

    Q_REQUIRED_RESULT AutoCorrectionSettings autoCorrectionSettings() const;
    void setAutoCorrectionSettings(const AutoCorrectionSettings &newAutoCorrectionSettings);

private:
    Q_REQUIRED_RESULT bool isFrenchLanguage() const;
    void readConfig();

    void fixTwoUppercaseChars();
    Q_REQUIRED_RESULT bool singleSpaces();
    void capitalizeWeekDays();
    Q_REQUIRED_RESULT bool autoFractions();
    void uppercaseFirstCharOfSentence();
    Q_REQUIRED_RESULT int advancedAutocorrect();
    void replaceTypographicQuotes();
    void superscriptAppendix();
    void addNonBreakingSpace();

    void selectPreviousWord(QTextCursor &cursor, int cursorPosition);
    void selectStringOnMaximumSearchString(QTextCursor &cursor, int cursorPosition);

    Q_REQUIRED_RESULT bool autoFormatURLs();
    Q_REQUIRED_RESULT bool autoBoldUnderline();

    Q_REQUIRED_RESULT QString autoDetectURL(const QString &_word) const;
    void readAutoCorrectionXmlFile(bool forceGlobal = false);
    Q_REQUIRED_RESULT bool excludeToUppercase(const QString &word) const;
    Q_REQUIRED_RESULT QColor linkColor();

    int mMaxFindStringLength = 0;
    int mMinFindStringLength = 0;
    QString mWord;
    QTextCursor mCursor;
    QChar mNonBreakingSpace;

    QString mAutoCorrectLang;
    QStringList mCacheNameOfDays;
    QSet<QString> mUpperCaseExceptions;
    QSet<QString> mTwoUpperLetterExceptions;
    QHash<QString, QString> mAutocorrectEntries;
    QHash<QString, QString> mSuperScriptEntries;
    AutoCorrectionUtils::TypographicQuotes mTypographicSingleQuotes;
    AutoCorrectionUtils::TypographicQuotes mTypographicDoubleQuotes;
    QColor mLinkColor;
    AutoCorrectionSettings mAutoCorrectionSettings;
};
}
