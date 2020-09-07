/*
   SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef ADDRESSEELINEEDITBALOO_H
#define ADDRESSEELINEEDITBALOO_H

#include <QStringList>

namespace PimCommon {
class BalooCompletionEmail;
class AddresseeLineEditBaloo
{
public:
    AddresseeLineEditBaloo();
    ~AddresseeLineEditBaloo();

    Q_REQUIRED_RESULT int balooCompletionSource() const;
    void setBalooCompletionSource(int value);

    Q_REQUIRED_RESULT QStringList balooBlackList() const;
    Q_REQUIRED_RESULT QStringList domainExcludeList() const;

    void loadBalooBlackList();
    Q_REQUIRED_RESULT QStringList cleanupEmailList(const QStringList &inputList);
private:
    PimCommon::BalooCompletionEmail *const mBalooCompletionEmail;
    QStringList mBalooBlackList;
    QStringList mDomainExcludeList;

    int mBalooCompletionSource = 0;
};
}

#endif // ADDRESSEELINEEDITBALOO_H
