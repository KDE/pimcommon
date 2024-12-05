/*
   SPDX-FileCopyrightText: 2017-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QMap>
#include <QObject>
class QTimer;

namespace KLDAPCore
{
class LdapClientSearch;
class LdapActivitiesAbstract;
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

    [[nodiscard]] QMap<int, int> ldapClientToCompletionSourceMap() const;
    [[nodiscard]] bool isLdapClientToCompletionSourceMapContains(int value) const;
    [[nodiscard]] int ldapClientToCompletionSourceValue(int value) const;

    [[nodiscard]] KLDAPCore::LdapClientSearch *ldapSearch() const;

    [[nodiscard]] QTimer *ldapTimer() const;
    [[nodiscard]] QString ldapText() const;
    void setLdapText(const QString &ldapText);

    [[nodiscard]] AddresseeLineEdit *addressLineEdit() const;
    void setAddressLineEdit(AddresseeLineEdit *addressLineEdit);

    void startLoadingLDAPEntries();
    void stopLDAPLookup();
    void restartLdap(const QString &searchString, AddresseeLineEdit *addressLine);

    void setLdapActivitiesAbstract(KLDAPCore::LdapActivitiesAbstract *ldapActivities);

private:
    // maps LDAP client indices to completion source indices
    // the assumption that they are always the first n indices in s_static->completion
    // does not hold when clients are added later on
    QMap<int, int> mLdapClientToCompletionSourceMap;
    QString mLdapText;
    QTimer *mLdapTimer = nullptr;
    AddresseeLineEdit *mAddressLineEdit = nullptr;
    KLDAPCore::LdapClientSearch *mLdapSearch = nullptr;
    KLDAPCore::LdapActivitiesAbstract *mLdapActivities = nullptr;

    AddresseeLineEditManager *mAddressLineStatic = nullptr;
};
}
