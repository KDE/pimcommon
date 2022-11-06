/*
  SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "autocorrectionsettings.h"
#include "autocorrection/export/exportlibreofficeautocorrection.h"
#include "autocorrection/import/importlibreofficeautocorrection.h"

#include "pimcommon_debug.h"
#include "settings/pimcommonsettings.h"

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QRegularExpression>
#include <QStandardPaths>
#include <QXmlStreamWriter>

using namespace PimCommon;
AutoCorrectionSettings::AutoCorrectionSettings()
{
    // default double quote open 0x201c
    // default double quote close 0x201d
    // default single quote open 0x2018
    // default single quote close 0x2019
    mTypographicSingleQuotes = AutoCorrectionUtils::typographicDefaultSingleQuotes();
    mTypographicDoubleQuotes = AutoCorrectionUtils::typographicDefaultDoubleQuotes();
    mDoubleFrenchQuotes = AutoCorrectionUtils::typographicDefaultFrenchQuotes();
    mNonBreakingSpace = QChar(QChar::Nbsp);
    readConfig();
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

bool AutoCorrectionSettings::isReplaceDoubleQuotesByFrenchQuotes() const
{
    return mReplaceDoubleQuotesByFrenchQuotes;
}

void AutoCorrectionSettings::setEnabledAutoCorrection(bool b)
{
    mEnabled = b;
}

void AutoCorrectionSettings::setReplaceDoubleQuotesByFrenchQuotes(bool b)
{
    mReplaceDoubleQuotesByFrenchQuotes = b;
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
    mReplaceDoubleQuotesByFrenchQuotes = PimCommon::PimCommonSettings::self()->replaceDoubleQuotesByFrenchQuotes();

    mTypographicSingleQuotes = AutoCorrectionUtils::TypographicQuotes::fromString(PimCommon::PimCommonSettings::self()->typographicSingleQuotes());
    if (mTypographicSingleQuotes.isEmpty()) {
        mTypographicSingleQuotes = AutoCorrectionUtils::typographicDefaultSingleQuotes();
    }
    mTypographicDoubleQuotes = AutoCorrectionUtils::TypographicQuotes::fromString(PimCommon::PimCommonSettings::self()->typographicDoubleQuotes());
    if (mTypographicDoubleQuotes.isEmpty()) {
        mTypographicDoubleQuotes = AutoCorrectionUtils::typographicDefaultDoubleQuotes();
    }
    readAutoCorrectionXmlFile();
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
    PimCommon::PimCommonSettings::self()->setTypographicSingleQuotes(mTypographicSingleQuotes.toString());
    PimCommon::PimCommonSettings::self()->setTypographicDoubleQuotes(mTypographicDoubleQuotes.toString());
    PimCommon::PimCommonSettings::self()->setReplaceDoubleQuotesByFrenchQuotes(mReplaceDoubleQuotesByFrenchQuotes);
    PimCommon::PimCommonSettings::self()->requestSync();
    writeAutoCorrectionXmlFile();
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
        readAutoCorrectionXmlFile(forceGlobal);
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
        writeAutoCorrectionXmlFile();
        return true;
    } else {
        return false;
    }
}

QChar AutoCorrectionSettings::nonBreakingSpace() const
{
    return mNonBreakingSpace;
}

void AutoCorrectionSettings::setNonBreakingSpace(const QChar &newNonBreakingSpace)
{
    mNonBreakingSpace = newNonBreakingSpace;
}

QHash<QString, QString> AutoCorrectionSettings::superScriptEntries() const
{
    return mSuperScriptEntries;
}

void AutoCorrectionSettings::setSuperScriptEntries(const QHash<QString, QString> &newSuperScriptEntries)
{
    mSuperScriptEntries = newSuperScriptEntries;
}

void AutoCorrectionSettings::setAutocorrectEntries(const QHash<QString, QString> &entries)
{
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
}

QHash<QString, QString> AutoCorrectionSettings::autocorrectEntries() const
{
    return mAutocorrectEntries;
}

void AutoCorrectionSettings::writeAutoCorrectionXmlFile(const QString &filename)
{
#if 1
    ExportLibreOfficeAutocorrection correct;
    correct.setAutocorrectEntries(mAutocorrectEntries);
    correct.setUpperCaseExceptions(mUpperCaseExceptions);
    correct.setTwoUpperLetterExceptions(mTwoUpperLetterExceptions);
    QString message;
    if (!correct.exportData(mAutoCorrectLang, filename, message)) {
        qCDebug(PIMCOMMON_LOG) << "We can't save in file :" << filename;
    }
#else
    ExportKMailAutocorrection correct;
    correct.setAutocorrectEntries(mAutocorrectEntries);
    correct.setUpperCaseExceptions(mUpperCaseExceptions);
    correct.setTwoUpperLetterExceptions(mTwoUpperLetterExceptions);
    QString message;
    if (!correct.exportData(mAutoCorrectLang, filename, message)) {
        qCDebug(PIMCOMMON_LOG) << "We can't save in file :" << filename;
    }
#endif
}

int AutoCorrectionSettings::maxFindStringLength() const
{
    return mMaxFindStringLength;
}

int AutoCorrectionSettings::minFindStringLength() const
{
    return mMinFindStringLength;
}

void AutoCorrectionSettings::loadLocalFileName(const QString &localFileName, const QString &fname)
{
    ImportLibreOfficeAutocorrection import;
    QString messageError;
    if (import.import(localFileName, messageError, ImportAbstractAutocorrection::All)) {
        mUpperCaseExceptions = import.upperCaseExceptions();
        mTwoUpperLetterExceptions = import.twoUpperLetterExceptions();
        mAutocorrectEntries = import.autocorrectEntries();
        // Don't import it in local
        // mSuperScriptEntries = import.superScriptEntries();
    }
    if (!fname.isEmpty() && import.import(fname, messageError, ImportAbstractAutocorrection::SuperScript)) {
        mSuperScriptEntries = import.superScriptEntries();
    }
    mMaxFindStringLength = import.maxFindStringLenght();
    mMinFindStringLength = import.minFindStringLenght();
}

void AutoCorrectionSettings::loadGlobalFileName(const QString &fname)
{
    if (fname.isEmpty()) {
        const QString fileName = AutoCorrectionUtils::containsAutoCorrectionFile(mAutoCorrectLang);
        if (!fileName.isEmpty()) {
            QString errorMessage;
            ImportLibreOfficeAutocorrection import;
            if (import.import(fileName, errorMessage)) {
                mUpperCaseExceptions = import.upperCaseExceptions();
                mTwoUpperLetterExceptions = import.twoUpperLetterExceptions();
                mAutocorrectEntries = import.autocorrectEntries();
                mSuperScriptEntries = import.superScriptEntries();
                mMaxFindStringLength = import.maxFindStringLenght();
                mMinFindStringLength = import.minFindStringLenght();
            }
        }
    } else {
        qDebug() << " import libreoffice file " << fname;
        ImportLibreOfficeAutocorrection import;
        QString messageError;
        if (import.import(fname, messageError, ImportAbstractAutocorrection::All)) {
            mUpperCaseExceptions = import.upperCaseExceptions();
            mTwoUpperLetterExceptions = import.twoUpperLetterExceptions();
            mAutocorrectEntries = import.autocorrectEntries();
            mSuperScriptEntries = import.superScriptEntries();
            mMaxFindStringLength = import.maxFindStringLenght();
            mMinFindStringLength = import.minFindStringLenght();
        }
    }
}

void AutoCorrectionSettings::migrateKMailXmlFile()
{
#if 0
    // TODO
    QString kdelang = QStringLiteral("en_US");
    const QStringList lst = QLocale::system().uiLanguages();
    if (!lst.isEmpty()) {
        kdelang = lst.at(0);
        if (kdelang == QLatin1Char('C')) {
            kdelang = QStringLiteral("en_US");
        }
    }
    static QRegularExpression reg(QStringLiteral("@.*"));
    kdelang.remove(reg);

    QString localFileName;
    static QRegularExpression regpath(QRegularExpression(QStringLiteral("_.*")));
    // Look at local file:
    if (!forceGlobal) {
        if (!mAutoCorrectLang.isEmpty()) {
            localFileName =
                QStandardPaths::locate(QStandardPaths::GenericDataLocation, QLatin1String("autocorrect/custom-") + mAutoCorrectLang + QLatin1String(".xml"));
        } else {
            if (!kdelang.isEmpty()) {
                localFileName =
                    QStandardPaths::locate(QStandardPaths::GenericDataLocation, QLatin1String("autocorrect/custom-") + kdelang + QLatin1String(".xml"));
            }
            if (localFileName.isEmpty() && kdelang.contains(QLatin1Char('_'))) {
                kdelang.remove(regpath);
                localFileName =
                    QStandardPaths::locate(QStandardPaths::GenericDataLocation, QLatin1String("autocorrect/custom-") + kdelang + QLatin1String(".xml"));
            }
        }
    }
    QString fname;
    // Load Global directly
    if (!mAutoCorrectLang.isEmpty()) {
        if (mAutoCorrectLang == QLatin1String("en_US")) {
            fname = QStandardPaths::locate(QStandardPaths::GenericDataLocation, QStringLiteral("autocorrect/autocorrect.xml"));
        } else {
            fname = QStandardPaths::locate(QStandardPaths::GenericDataLocation, QLatin1String("autocorrect/") + mAutoCorrectLang + QLatin1String(".xml"));
        }
    } else {
        if (fname.isEmpty() && !kdelang.isEmpty()) {
            fname = QStandardPaths::locate(QStandardPaths::GenericDataLocation, QLatin1String("autocorrect/") + kdelang + QLatin1String(".xml"));
        }
        if (fname.isEmpty() && kdelang.contains(QLatin1Char('_'))) {
            kdelang.remove(regpath);
            fname = QStandardPaths::locate(QStandardPaths::GenericDataLocation, QLatin1String("autocorrect/") + kdelang + QLatin1String(".xml"));
        }
    }
    if (fname.isEmpty()) {
        fname = QStandardPaths::locate(QStandardPaths::GenericDataLocation, QStringLiteral("autocorrect/autocorrect.xml"));
    }

    if (mAutoCorrectLang.isEmpty()) {
        mAutoCorrectLang = kdelang;
    }
#endif
}

void AutoCorrectionSettings::readAutoCorrectionXmlFile(bool forceGlobal)
{
    mUpperCaseExceptions.clear();
    mAutocorrectEntries.clear();
    mTwoUpperLetterExceptions.clear();
    mSuperScriptEntries.clear();

    QString kdelang = QStringLiteral("en-US");
    const QStringList lst = QLocale::system().uiLanguages();
    if (!lst.isEmpty()) {
        kdelang = lst.at(0);
        if (kdelang == QLatin1Char('C')) {
            kdelang = QStringLiteral("en-US");
        }
    }
    static QRegularExpression reg(QStringLiteral("@.*"));
    kdelang.remove(reg);

    QString localFileName;
    static QRegularExpression regpath(QRegularExpression(QStringLiteral("_.*")));
    // Look at local file:
    if (!forceGlobal) {
        if (mAutoCorrectLang.isEmpty()) {
            if (!kdelang.isEmpty()) {
                localFileName = AutoCorrectionUtils::containsAutoCorrectionFile(kdelang);
            }
            if (localFileName.isEmpty() && kdelang.contains(QLatin1Char('_'))) {
                kdelang.remove(regpath);
                localFileName = AutoCorrectionUtils::containsAutoCorrectionFile(kdelang);
            }
        }
    }
    QString fname;
    // Load Global directly
    if (!mAutoCorrectLang.isEmpty()) {
        localFileName = AutoCorrectionUtils::containsAutoCorrectionFile(mAutoCorrectLang);
    } else {
        if (fname.isEmpty() && !kdelang.isEmpty()) {
            fname = AutoCorrectionUtils::containsAutoCorrectionFile(kdelang);
        }
        if (fname.isEmpty() && kdelang.contains(QLatin1Char('_'))) {
            kdelang.remove(regpath);
            fname = AutoCorrectionUtils::containsAutoCorrectionFile(kdelang);
        }
    }

    if (mAutoCorrectLang.isEmpty()) {
        mAutoCorrectLang = kdelang;
    }
    // qDebug() << " fname :" << fname;
    // qDebug() << " localFileName:" << localFileName;

    if (localFileName.isEmpty()) {
        loadGlobalFileName(fname);
    } else {
        loadLocalFileName(localFileName, fname);
    }
}

AutoCorrectionUtils::TypographicQuotes AutoCorrectionSettings::doubleFrenchQuotes() const
{
    return mDoubleFrenchQuotes;
}

void AutoCorrectionSettings::setDoubleFrenchQuotes(const AutoCorrectionUtils::TypographicQuotes &newDoubleFrenchQuotes)
{
    mDoubleFrenchQuotes = newDoubleFrenchQuotes;
}

QDebug operator<<(QDebug d, const PimCommon::AutoCorrectionSettings &t)
{
    d << "mAddNonBreakingSpace " << t.nonBreakingSpace();
    d << "mSuperScriptAppendix " << t.isSuperScript();
    d << "mEnabled " << t.isEnabledAutoCorrection();
    d << "mAutoBoldUnderline " << t.isAutoBoldUnderline();
    d << "mAutoFormatUrl " << t.isAutoFormatUrl();
    d << "mReplaceSingleQuotes " << t.isReplaceSingleQuotes();
    d << "mReplaceDoubleQuotes " << t.isReplaceDoubleQuotes();
    d << "mAdvancedAutocorrect " << t.isAdvancedAutocorrect();
    d << "mCapitalizeWeekDays " << t.isCapitalizeWeekDays();
    d << "mAutoFractions " << t.isAutoFractions();
    d << "mFixTwoUppercaseChars " << t.isFixTwoUppercaseChars();
    d << "mUppercaseFirstCharOfSentence " << t.isUppercaseFirstCharOfSentence();
    d << "mSingleSpaces " << t.isSingleSpaces();
    d << "mMaxFindStringLength " << t.maxFindStringLength();
    d << "mMinFindStringLength " << t.minFindStringLength();
    d << "mNonBreakingSpace " << t.nonBreakingSpace();
    d << "mAutoCorrectLang " << t.language();
    d << "mTwoUpperLetterExceptions " << t.twoUpperLetterExceptions();
    d << "mUpperCaseExceptions " << t.upperCaseExceptions();
    d << "mSuperScriptEntries " << t.superScriptEntries();
    d << "mAutocorrectEntries " << t.autocorrectEntries();
    d << "mTypographicDoubleQuotes " << t.typographicDoubleQuotes();
    d << "mTypographicSingleQuotes " << t.typographicSingleQuotes();
    d << "mReplaceDoubleQuotesByFrenchQuotes " << t.isReplaceDoubleQuotesByFrenchQuotes();
    return d;
}
