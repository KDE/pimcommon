/*
  SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
  code based on kdenlive
*/

#include "needupdateversionutils.h"

#include <KConfigGroup>
#include <KSharedConfig>

#include <QRegularExpression>

PimCommon::NeedUpdateVersionUtils::ObsoleteVersion PimCommon::NeedUpdateVersionUtils::obsoleteVersionStatus(const QString &str, QDate currentDate)
{
    static QRegularExpression regular{QStringLiteral("\\((.*)\\)")};
    QRegularExpressionMatch match;
    QString captured;
    if (str.contains(regular, &match)) {
        captured = match.captured(1);
    } else {
        captured = str;
    }
    if (!captured.isEmpty()) {
        const QStringList version = captured.split(QLatin1Char('.'));
        if (version.size() > 2) {
            bool ok;
            int year = version.at(0).toInt(&ok);
            if (ok) {
                const int month = version.at(1).toInt(&ok);
                if (ok) {
                    if (year < 100) {
                        year += 2000;
                    }
                    const QDate releaseDate = QDate(year, month, 1);
                    if (releaseDate.isValid()) {
                        const int days = releaseDate.daysTo(currentDate);
                        if (days > 180) {
                            if (days > 360) {
                                return PimCommon::NeedUpdateVersionUtils::ObsoleteVersion::OlderThan12Months;
                            }
                            return PimCommon::NeedUpdateVersionUtils::ObsoleteVersion::OlderThan6Months;
                        }
                    }
                }
            }
        }
    } else {
        return PimCommon::NeedUpdateVersionUtils::ObsoleteVersion::Unknown;
    }
    return PimCommon::NeedUpdateVersionUtils::ObsoleteVersion::NotObsoleteYet;
}

void PimCommon::NeedUpdateVersionUtils::disableCheckVersion()
{
    KSharedConfig::Ptr config = KSharedConfig::openConfig();
    KConfigGroup group(config, QStringLiteral("Check Version"));
    group.writeEntry("checkerVersionEnabled", false);
}

bool PimCommon::NeedUpdateVersionUtils::checkVersion()
{
#if ENABLE_WARN_OUTDATED == 1
    KSharedConfig::Ptr config = KSharedConfig::openConfig();
    KConfigGroup group(config, QStringLiteral("Check Version"));
    return group.readEntry("checkerVersionEnabled", true);
#else
    return false;
#endif
}

QDate PimCommon::NeedUpdateVersionUtils::compileDate()
{
    return QDate::fromString(QString::fromLatin1(__DATE__), QStringLiteral("MMM dd yyyy"));
}
