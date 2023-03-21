/*
  SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#pragma once
#include "pimcommonakonadi_private_export.h"
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
    };

    Q_REQUIRED_RESULT QStringList cleanupEmailList();

    Q_REQUIRED_RESULT BalooCompletionEmailInfo balooCompletionEmailInfo() const;
    void setBalooCompletionEmailInfo(const BalooCompletionEmailInfo &newBalooCompletionEmailInfo);

private:
    Q_REQUIRED_RESULT QString stripEmail(const QString &email, QString &address);
    BalooCompletionEmailInfo mBalooCompletionEmailInfo;
};
}
