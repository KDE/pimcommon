/*
  SPDX-FileCopyrightText: 2015-2024 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#pragma once
#include "pimcommonakonadi_private_export.h"
#include <QRegularExpression>
#include <QStringList>
namespace PimCommon
{
class PIMCOMMONAKONADI_TESTS_EXPORT BalooCompletionEmail
{
public:
    BalooCompletionEmail();
    struct BalooCompletionEmailInfo {
        QStringList mListEmail;
        QStringList mExcludeDomains;
        QStringList mBlackList;
        QStringList mExcludeEmailsRegularExpressions;
    };

    [[nodiscard]] QStringList cleanupEmailList();

    [[nodiscard]] BalooCompletionEmailInfo balooCompletionEmailInfo() const;
    void setBalooCompletionEmailInfo(const BalooCompletionEmailInfo &newBalooCompletionEmailInfo);

private:
    [[nodiscard]] QString stripEmail(const QString &email, QString &address);
    BalooCompletionEmailInfo mBalooCompletionEmailInfo;
    static QList<QRegularExpression> mExcludeEmailsRegularExpressions;
};
}
