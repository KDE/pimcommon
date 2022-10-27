/*
  SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "autocorrectionutils.h"
#include <QDir>
#include <QFileInfo>
#include <QStandardPaths>
using namespace PimCommon;
AutoCorrectionUtils::TypographicQuotes AutoCorrectionUtils::typographicDefaultSingleQuotes()
{
    TypographicQuotes quote;
    quote.begin = QChar(0x2018);
    quote.end = QChar(0x2019);
    return quote;
}

AutoCorrectionUtils::TypographicQuotes AutoCorrectionUtils::typographicDefaultDoubleQuotes()
{
    TypographicQuotes quote;
    quote.begin = QChar(0x201c);
    quote.end = QChar(0x201d);
    return quote;
}

AutoCorrectionUtils::TypographicQuotes AutoCorrectionUtils::typographicDefaultFrenchQuotes()
{
    TypographicQuotes quote;
    quote.begin = QChar(0x00AB);
    quote.end = QChar(0x00BB);
    return quote;
}

QDebug operator<<(QDebug d, PimCommon::AutoCorrectionUtils::TypographicQuotes t)
{
    d << "TypographicQuotes.begin " << t.begin;
    d << "TypographicQuotes.end " << t.end;
    return d;
}

QString AutoCorrectionUtils::libreofficeFile(const QString &lang)
{
    return QStringLiteral("acor_%1.dat").arg(lang);
}

QStringList AutoCorrectionUtils::libreOfficeAutoCorrectionPath()
{
    QStringList dirList;
    auto maybeAddPath = [&dirList](const QString &path) {
        if (QFileInfo::exists(path)) {
            dirList.append(path);
        }
    };
    dirList.append(
        QStandardPaths::locateAll(QStandardPaths::GenericConfigLocation, QStringLiteral("libreoffice/4/user/autocorr/"), QStandardPaths::LocateDirectory));
    maybeAddPath(QStringLiteral("/usr/lib64/libreoffice/share/autocorr/"));
    return dirList;
}

QStringList AutoCorrectionUtils::searchAutoCorrectLibreOfficeFiles()
{
    QStringList files;
    const QString path = QStringLiteral("/usr/lib64/libreoffice/share/autocorr/");
    if (QFileInfo::exists(path)) {
        QDir dir(path);
        const QStringList entryList = dir.entryList(QDir::Files | QDir::NoDotAndDotDot);
        for (const QString &file : entryList) {
            QString curFile = file;
            curFile.remove(path);
            curFile.remove(QStringLiteral(".dat"));
            curFile.remove(QStringLiteral("acor_"));
            files.append(curFile);
        }
    }
    return files;
}

QStringList AutoCorrectionUtils::autoCorrectLibreOfficeLanguageToString(const QStringList &langs)
{
    QStringList languagesStr;
    const QList<QLocale> allLocales = QLocale::matchingLocales(QLocale::AnyLanguage, QLocale::AnyScript, QLocale::AnyCountry);
    for (const QLocale &locale : allLocales) {
        const QString languageCode = locale.name();
        for (const QString &lang : langs) {
            if (languageCode == lang) {
                const QString nativeName = locale.nativeLanguageName();
                // For some languages the native name might be empty.
                // In this case use the non native language name as fallback.
                // See: QTBUG-51323
                const QString languageName = nativeName.isEmpty() ? QLocale::languageToString(locale.language()) : nativeName;
                languagesStr.append(languageName);
                break;
            } else {
                QString b = lang;
                b.replace(QLatin1Char('-'), QLatin1Char('_'));
                if (languageCode == b) {
                    const QString nativeName = locale.nativeLanguageName();
                    // For some languages the native name might be empty.
                    // In this case use the non native language name as fallback.
                    // See: QTBUG-51323
                    const QString languageName = nativeName.isEmpty() ? QLocale::languageToString(locale.language()) : nativeName;
                    languagesStr.append(languageName);
                    break;
                }
            }
        }
    }
    return languagesStr;
}
