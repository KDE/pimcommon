/*
  SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "pimcommon_export.h"
#include <QChar>
#include <QDebug>
namespace PimCommon
{
namespace AutoCorrectionUtils
{
struct TypographicQuotes {
    QChar begin;
    QChar end;
    Q_REQUIRED_RESULT QString toString() const;
    Q_REQUIRED_RESULT bool isEmpty() const;
    Q_REQUIRED_RESULT static TypographicQuotes fromString(const QString &str);
};

Q_REQUIRED_RESULT PIMCOMMON_EXPORT TypographicQuotes typographicDefaultSingleQuotes();
Q_REQUIRED_RESULT PIMCOMMON_EXPORT TypographicQuotes typographicDefaultDoubleQuotes();
Q_REQUIRED_RESULT PIMCOMMON_EXPORT TypographicQuotes typographicDefaultFrenchQuotes();
Q_REQUIRED_RESULT PIMCOMMON_EXPORT QString libreofficeFile(const QString &lang);
Q_REQUIRED_RESULT PIMCOMMON_EXPORT QStringList libreOfficeAutoCorrectionPath();
Q_REQUIRED_RESULT PIMCOMMON_EXPORT QStringList searchAutoCorrectLibreOfficeFiles();
Q_REQUIRED_RESULT PIMCOMMON_EXPORT QStringList autoCorrectLibreOfficeLanguageToString(const QStringList &langs);
Q_REQUIRED_RESULT PIMCOMMON_EXPORT QString libreOfficeLocalAutoCorrectionPath();
Q_REQUIRED_RESULT PIMCOMMON_EXPORT QString containsAutoCorrectionFile(const QString &lang);
Q_REQUIRED_RESULT PIMCOMMON_EXPORT QString libreOfficeSystemPath();
};
}
PIMCOMMON_EXPORT QDebug operator<<(QDebug d, PimCommon::AutoCorrectionUtils::TypographicQuotes t);
