/*
  SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#ifndef BALOOCOMPLETIONEMAIL_H
#define BALOOCOMPLETIONEMAIL_H
#include <QStringList>
#include "pimcommonakonadi_private_export.h"
namespace PimCommon {
class PIMCOMMONAKONADI_TESTS_EXPORT BalooCompletionEmail
{
public:
    BalooCompletionEmail();
    void setEmailList(const QStringList &lst);
    void setExcludeDomain(const QStringList &lst);

    void setBlackList(const QStringList &lst);

    Q_REQUIRED_RESULT QStringList cleanupEmailList();
private:
    Q_REQUIRED_RESULT QString stripEmail(const QString &email, QString &address);
    QStringList mListEmail;
    QStringList mExcludeDomain;
    QStringList mBlackList;
};
}

#endif // BALOOCOMPLETIONEMAIL_H
