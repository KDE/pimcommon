/*
  SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "akonadisearchcompletionemail.h"
#include <KEmailAddress>
#include <QMap>
#include <QRegularExpression>

using namespace PimCommon;

AkonadiSearchCompletionEmail::AkonadiSearchCompletionEmail() = default;
QList<QRegularExpression> AkonadiSearchCompletionEmail::mExcludeEmailsRegularExpressions = {};
QStringList AkonadiSearchCompletionEmail::cleanupEmailList()
{
    if (mAkonadiSearchCompletionEmailInfo.mListEmail.isEmpty()) {
        return {};
    }
    QMap<QString, QString> hashEmail;
    for (QString email : std::as_const(mAkonadiSearchCompletionEmailInfo.mListEmail)) {
        if (!mAkonadiSearchCompletionEmailInfo.mBlackList.contains(email)) {
            QString address;
            email = stripEmail(email, address);
            if (address.isEmpty()) {
                address = email;
            }
            bool excludeMail = false;
            for (const QString &excludeDomain : std::as_const(mAkonadiSearchCompletionEmailInfo.mExcludeDomains)) {
                if (!excludeDomain.isEmpty()) {
                    if (address.endsWith(excludeDomain)) {
                        excludeMail = true;
                        continue;
                    }
                }
            }
            if (!excludeMail) {
                for (const QRegularExpression &excludeEmailRegularExpression : std::as_const(mExcludeEmailsRegularExpressions)) {
                    if (address.contains(excludeEmailRegularExpression)) {
                        excludeMail = true;
                        continue;
                    }
                }
            }

            const QString addressLower = address.toLower();
            if (!excludeMail && !hashEmail.contains(addressLower)) {
                hashEmail.insert(addressLower, email);
            }
        }
    }
    return hashEmail.values();
}

/* stips the name of an email address email
 *
 * 'a' <a@example.com> -> a <a@example.com>
 * "a" <a@example.com> -> a <a@example.com>
 * "\"'a'\"" <a@example.com> -> a <a@example.com>
 *
 * but "\"'a" <a@example.com> -> "\"'a" <a@example.com>
 * cause the start and end is not the same.
 */
QString AkonadiSearchCompletionEmail::stripEmail(const QString &email, QString &address)
{
    QString displayName;
    QString addrSpec;
    QString comment;
    if (KEmailAddress::AddressOk == KEmailAddress::splitAddress(email, displayName, addrSpec, comment)) {
        address = addrSpec;
        while (true) {
            if ((displayName.startsWith(QLatin1StringView("\\\"")) && displayName.endsWith(QLatin1StringView("\\\"")))) {
                displayName = displayName.mid(2, displayName.length() - 4).trimmed();
            } else if ((displayName.startsWith(QLatin1Char('\'')) && displayName.endsWith(QLatin1Char('\'')))
                       || (displayName.startsWith(QLatin1Char('"')) && displayName.endsWith(QLatin1Char('"')))) {
                displayName = displayName.mid(1, displayName.length() - 2).trimmed();
            } else {
                break;
            }
        }
        return KEmailAddress::normalizedAddress(displayName, addrSpec, comment);
    } else {
        return email;
    }
}

AkonadiSearchCompletionEmail::AkonadiSearchCompletionEmailInfo AkonadiSearchCompletionEmail::balooCompletionEmailInfo() const
{
    return mAkonadiSearchCompletionEmailInfo;
}

void AkonadiSearchCompletionEmail::setBalooCompletionEmailInfo(const AkonadiSearchCompletionEmailInfo &newBalooCompletionEmailInfo)
{
    mAkonadiSearchCompletionEmailInfo = newBalooCompletionEmailInfo;
    mExcludeEmailsRegularExpressions.clear();
    for (const auto &str : std::as_const(mAkonadiSearchCompletionEmailInfo.mExcludeEmailsRegularExpressions)) {
        const QRegularExpression exp(str);
        if (exp.isValid()) {
            mExcludeEmailsRegularExpressions.append(exp);
        }
    }
}
