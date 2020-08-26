/*
   Copyright (C) 2017-2020 Laurent Montel <montel@kde.org>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
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
    PimCommon::BalooCompletionEmail *mBalooCompletionEmail = nullptr;
    QStringList mBalooBlackList;
    QStringList mDomainExcludeList;

    int mBalooCompletionSource = 0;
};
}

#endif // ADDRESSEELINEEDITBALOO_H
