/*
   SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "addresseelineeditutil.h"
using namespace Qt::Literals::StringLiterals;

#include <QRegularExpression>
#include <QUrl>

QString PimCommon::AddresseeLineEditUtil::adaptPasteMails(const QString &str)
{
    QString newText = str;
    // remove newlines in the to-be-pasted string
    static QRegularExpression reg2("\r?\n"_L1);
    QStringList lines = newText.split(reg2, Qt::SkipEmptyParts);
    QStringList::iterator end(lines.end());
    for (QStringList::iterator it = lines.begin(); it != end; ++it) {
        // remove trailing commas and whitespace
        static QRegularExpression reg1(QRegularExpression(",?\\s*$"_L1));
        (*it).remove(reg1);
    }
    newText = lines.join(", "_L1);

    if (newText.startsWith("mailto:"_L1)) {
        const QUrl url(newText);
        newText = url.path();
    } else if (newText.contains(" at "_L1)) {
        // Anti-spam stuff
        newText.replace(QStringLiteral(" at "), QStringLiteral("@"));
        newText.replace(QStringLiteral(" dot "), QStringLiteral("."));
    } else if (newText.contains("(at)"_L1)) {
        static QRegularExpression reg("\\s*\\(at\\)\\s*"_L1);
        newText.replace(reg, QStringLiteral("@"));
    }
    return newText;
}
