/*
  SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#pragma once
#include "pimcommonakonadi_private_export.h"
#include <QRegularExpression>
#include <QStringList>
namespace PimCommon
{
class PIMCOMMONAKONADI_TESTS_EXPORT AkonadiSearchCompletionEmail
{
public:
    AkonadiSearchCompletionEmail();
    struct AkonadiSearchCompletionEmailInfo {
        QStringList mListEmail;
        QStringList mExcludeDomains;
        QStringList mBlackList;
        QStringList mExcludeEmailsRegularExpressions;
    };

    [[nodiscard]] QStringList cleanupEmailList();

    [[nodiscard]] AkonadiSearchCompletionEmailInfo balooCompletionEmailInfo() const;
    void setBalooCompletionEmailInfo(const AkonadiSearchCompletionEmailInfo &newBalooCompletionEmailInfo);

private:
    [[nodiscard]] QString stripEmail(const QString &email, QString &address);
    AkonadiSearchCompletionEmailInfo mAkonadiSearchCompletionEmailInfo;
    static QList<QRegularExpression> mExcludeEmailsRegularExpressions;
};
}
