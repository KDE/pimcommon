/*
  SPDX-FileCopyrightText: 2012-2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "autocorrectionsettings.h"
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

    void writeConfig();

    bool autocorrect(bool htmlMode, QTextDocument &document, int &position);

    void loadGlobalFileName(const QString &fname);

    Q_REQUIRED_RESULT AutoCorrectionSettings autoCorrectionSettings() const;
    void setAutoCorrectionSettings(const AutoCorrectionSettings &newAutoCorrectionSettings);

    void writeAutoCorrectionXmlFile(const QString &filename);

private:
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
    Q_REQUIRED_RESULT bool excludeToUppercase(const QString &word) const;
    Q_REQUIRED_RESULT QColor linkColor();

    QString mWord;
    QTextCursor mCursor;

    QStringList mCacheNameOfDays;
    QColor mLinkColor;
    // Settings
    AutoCorrectionSettings mAutoCorrectionSettings;
};
}
