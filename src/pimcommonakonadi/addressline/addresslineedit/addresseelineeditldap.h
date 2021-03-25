/*
   SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QMap>
#include <QTimer>

namespace KLDAP
{
class LdapClientSearch;
}

namespace PimCommon
{
class AddresseeLineEditManager;
class AddresseeLineEdit;
class AddresseeLineEditLdap : public QObject
{
public:
    explicit AddresseeLineEditLdap(AddresseeLineEditManager *addressLineStatic, QObject *parent = nullptr);
    ~AddresseeLineEditLdap() override;

    void init();

    void updateLDAPWeights();

    QMap<int, int> ldapClientToCompletionSourceMap() const;
    bool isLdapClientToCompletionSourceMapContains(int value) const;
    int ldapClientToCompletionSourceValue(int value) const;

    KLDAP::LdapClientSearch *ldapSearch() const;

    QTimer *ldapTimer() const;
    Q_REQUIRED_RESULT QString ldapText() const;
    void setLdapText(const QString &ldapText);

    AddresseeLineEdit *addressLineEdit() const;
    void setAddressLineEdit(AddresseeLineEdit *addressLineEdit);

    void startLoadingLDAPEntries();
    void stopLDAPLookup();
    void restartLdap(const QString &searchString, AddresseeLineEdit *addressLine);

private:
    // maps LDAP client indices to completion source indices
    // the assumption that they are always the first n indices in s_static->completion
    // does not hold when clients are added later on
    QMap<int, int> mLdapClientToCompletionSourceMap;
    QString mLdapText;
    QTimer *mLdapTimer = nullptr;
    AddresseeLineEdit *mAddressLineEdit = nullptr;
    KLDAP::LdapClientSearch *mLdapSearch = nullptr;

    AddresseeLineEditManager *mAddressLineStatic = nullptr;
};
}

