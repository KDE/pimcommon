/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "addresseelineeditutil.h"
#include <QRegularExpression>
#include <QUrl>

QString PimCommon::AddresseeLineEditUtil::adaptPasteMails(const QString &str)
{
    QString newText = str;
    // remove newlines in the to-be-pasted string
    QStringList lines = newText.split(QRegularExpression(QStringLiteral("\r?\n")), Qt::SkipEmptyParts);
    QStringList::iterator end(lines.end());
    for (QStringList::iterator it = lines.begin(); it != end; ++it) {
        // remove trailing commas and whitespace
        (*it).remove(QRegularExpression(QStringLiteral(",?\\s*$")));
    }
    newText = lines.join(QLatin1String(", "));

    if (newText.startsWith(QLatin1String("mailto:"))) {
        const QUrl url(newText);
        newText = url.path();
    } else if (newText.contains(QLatin1String(" at "))) {
        // Anti-spam stuff
        newText.replace(QStringLiteral(" at "), QStringLiteral("@"));
        newText.replace(QStringLiteral(" dot "), QStringLiteral("."));
    } else if (newText.contains(QLatin1String("(at)"))) {
        newText.replace(QRegularExpression(QStringLiteral("\\s*\\(at\\)\\s*")), QStringLiteral("@"));
    }
    return newText;
}
