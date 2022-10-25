/*
  SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "autocorrectionsettings.h"
#include "autocorrection/import/importkmailautocorrection.h"
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
    mNonBreakingSpace = QChar(QChar::Nbsp);
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
    const QString fname = filename.isEmpty() ? QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation) + QLatin1String("/autocorrect/custom-")
            + (mAutoCorrectLang == QLatin1String("en_US") ? QStringLiteral("autocorrect") : mAutoCorrectLang) + QLatin1String(".xml")
                                             : filename;
    QFileInfo fileInfo(fname);
    QDir().mkpath(fileInfo.absolutePath());
    QFile file(fname);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qCDebug(PIMCOMMON_LOG) << "We can't save in file :" << fname;
        return;
    }

    QXmlStreamWriter streamWriter(&file);

    streamWriter.setAutoFormatting(true);
    streamWriter.setAutoFormattingIndent(2);
    streamWriter.writeStartDocument();

    streamWriter.writeDTD(QStringLiteral("<!DOCTYPE autocorrection>"));

    streamWriter.writeStartElement(QStringLiteral("Word"));

    streamWriter.writeStartElement(QStringLiteral("items"));
    QHashIterator<QString, QString> i(mAutocorrectEntries);
    while (i.hasNext()) {
        i.next();
        streamWriter.writeStartElement(QStringLiteral("item"));
        streamWriter.writeAttribute(QStringLiteral("find"), i.key());
        streamWriter.writeAttribute(QStringLiteral("replace"), i.value());
        streamWriter.writeEndElement();
    }
    streamWriter.writeEndElement();

    streamWriter.writeStartElement(QStringLiteral("UpperCaseExceptions"));
    QSet<QString>::const_iterator upper = mUpperCaseExceptions.constBegin();
    while (upper != mUpperCaseExceptions.constEnd()) {
        streamWriter.writeStartElement(QStringLiteral("word"));
        streamWriter.writeAttribute(QStringLiteral("exception"), *upper);
        ++upper;
        streamWriter.writeEndElement();
    }
    streamWriter.writeEndElement();

    streamWriter.writeStartElement(QStringLiteral("TwoUpperLetterExceptions"));
    QSet<QString>::const_iterator twoUpper = mTwoUpperLetterExceptions.constBegin();
    while (twoUpper != mTwoUpperLetterExceptions.constEnd()) {
        streamWriter.writeStartElement(QStringLiteral("word"));
        streamWriter.writeAttribute(QStringLiteral("exception"), *twoUpper);
        ++twoUpper;
        streamWriter.writeEndElement();
    }
    streamWriter.writeEndElement();

    streamWriter.writeStartElement(QStringLiteral("DoubleQuote"));
    streamWriter.writeStartElement(QStringLiteral("doublequote"));
    streamWriter.writeAttribute(QStringLiteral("begin"), mTypographicDoubleQuotes.begin);
    streamWriter.writeAttribute(QStringLiteral("end"), mTypographicDoubleQuotes.end);
    streamWriter.writeEndElement();
    streamWriter.writeEndElement();

    streamWriter.writeStartElement(QStringLiteral("SimpleQuote"));
    streamWriter.writeStartElement(QStringLiteral("simplequote"));
    streamWriter.writeAttribute(QStringLiteral("begin"), mTypographicSingleQuotes.begin);
    streamWriter.writeAttribute(QStringLiteral("end"), mTypographicSingleQuotes.end);
    streamWriter.writeEndElement();
    streamWriter.writeEndElement();

    streamWriter.writeEndDocument();
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
    ImportKMailAutocorrection import;
    QString messageError;
    if (import.import(localFileName, messageError, ImportAbstractAutocorrection::All)) {
        mUpperCaseExceptions = import.upperCaseExceptions();
        mTwoUpperLetterExceptions = import.twoUpperLetterExceptions();
        mAutocorrectEntries = import.autocorrectEntries();
        mTypographicSingleQuotes = import.typographicSingleQuotes();
        mTypographicDoubleQuotes = import.typographicDoubleQuotes();
        // Don't import it in local
        // mSuperScriptEntries = import.superScriptEntries();
    }
    if (!fname.isEmpty() && import.import(fname, messageError, ImportAbstractAutocorrection::SuperScript)) {
        mSuperScriptEntries = import.superScriptEntries();
    }
    mMaxFindStringLength = import.maxFindStringLenght();
    mMinFindStringLength = import.minFindStringLenght();
}

void AutoCorrectionSettings::loadGlobalFileName(const QString &fname, bool forceGlobal)
{
    if (fname.isEmpty()) {
        mTypographicSingleQuotes = AutoCorrectionUtils::typographicDefaultSingleQuotes();
        mTypographicDoubleQuotes = AutoCorrectionUtils::typographicDefaultDoubleQuotes();
    } else {
        ImportKMailAutocorrection import;
        QString messageError;
        if (import.import(fname, messageError, ImportAbstractAutocorrection::All)) {
            mUpperCaseExceptions = import.upperCaseExceptions();
            mTwoUpperLetterExceptions = import.twoUpperLetterExceptions();
            mAutocorrectEntries = import.autocorrectEntries();
            mTypographicSingleQuotes = import.typographicSingleQuotes();
            mTypographicDoubleQuotes = import.typographicDoubleQuotes();
            mSuperScriptEntries = import.superScriptEntries();
            if (forceGlobal) {
                mTypographicSingleQuotes = AutoCorrectionUtils::typographicDefaultSingleQuotes();
                mTypographicDoubleQuotes = AutoCorrectionUtils::typographicDefaultDoubleQuotes();
            }
            mMaxFindStringLength = import.maxFindStringLenght();
            mMinFindStringLength = import.minFindStringLenght();
        }
    }
}

void AutoCorrectionSettings::readAutoCorrectionXmlFile(bool forceGlobal)
{
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

    mUpperCaseExceptions.clear();
    mAutocorrectEntries.clear();
    mTwoUpperLetterExceptions.clear();
    mSuperScriptEntries.clear();

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
    // qCDebug(PIMCOMMON_LOG)<<" fname :"<<fname;
    // qCDebug(PIMCOMMON_LOG)<<" LocalFile:"<<LocalFile;

    if (localFileName.isEmpty()) {
        loadGlobalFileName(fname, forceGlobal);
    } else {
        loadLocalFileName(localFileName, fname);
    }
}
