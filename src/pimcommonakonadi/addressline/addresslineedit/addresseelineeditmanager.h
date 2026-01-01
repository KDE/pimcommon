/*
  SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <Akonadi/Collection>
#include <QMap>

#include <Akonadi/Item>
#include <Akonadi/Session>
#include <KLDAPCore/LdapClientSearch>
#include <QList>
#include <QPointer>

#include <QColor>

class QTimer;
namespace KLDAPCore
{
class LdapActivitiesAbstract;
}

namespace PimCommon
{
class KMailCompletion;
class AddresseeLineEdit;
class AddresseeLineEditAkonadi;
class AddresseeLineEditLdap;
class AddresseeLineEditAkonadiSearch;
class AddresseeLineEditManager
{
public:
    using CompletionItemsMap = QMap<QString, QPair<int, int>>;

    AddresseeLineEditManager();

    ~AddresseeLineEditManager();

    static AddresseeLineEditManager *self();

    void updateCollectionWeights();

    void updateLDAPWeights();
    void updateCompletionOrder();

    [[nodiscard]] int addCompletionSource(const QString &source, int weight);
    void removeCompletionSource(const QString &source);

    CompletionItemsMap completionItemMap;
    QStringList completionSources;

    // The weights associated with the completion sources in s_static->completionSources.
    // Both are maintained by addCompletionSource(), don't attempt to modify those yourself.
    QMap<QString, int> completionSourceWeights;

    // holds the cached mapping from akonadi collection id to the completion source index
    struct collectionInfo {
        collectionInfo()
        {
        }

        collectionInfo(int idx, bool _enabled)
            : index(idx)
            , enabled(_enabled)
        {
        }

        int index = -1;
        bool enabled = true;
    };

    QMap<Akonadi::Collection::Id, collectionInfo> akonadiCollectionToCompletionSourceMap;
    // a list of akonadi items (contacts) that have not had their collection fetched yet
    Akonadi::Item::List akonadiPendingItems;
    QList<QPointer<Akonadi::Job>> akonadiJobsInFlight;

    // Ldap
    void initializeLdap();
    [[nodiscard]] QString ldapText() const;
    void setLdapText(const QString &ldapText);
    KLDAPCore::LdapClientSearch *ldapSearch() const;
    QTimer *ldapTimer() const;
    [[nodiscard]] bool isLdapClientToCompletionSourceMapContains(int value) const;
    [[nodiscard]] int ldapClientToCompletionSourceValue(int value) const;
    void stopLDAPLookup();
    void startLoadingLDAPEntries();
    void restartLdap(const QString &searchString, AddresseeLineEdit *addressLine);

    // Baloo
    [[nodiscard]] int balooCompletionSource() const;
    void setBalooCompletionSource(int value);

    // Akonadi
    [[nodiscard]] Akonadi::Session *akonadiSession() const;

    [[nodiscard]] KMailCompletion *completion() const;

    [[nodiscard]] AddresseeLineEdit *addressLineEdit() const;
    void setAddressLineEdit(AddresseeLineEdit *addressLineEdit);
    [[nodiscard]] bool isOnline() const;

    void loadBalooBlackList();
    [[nodiscard]] QStringList cleanupEmailList(const QStringList &inputList);
    [[nodiscard]] QStringList balooBlackList() const;

    [[nodiscard]] bool showOU() const;
    void setShowOU(bool showOU);

    [[nodiscard]] bool autoGroupExpand() const;
    void setAutoGroupExpand(bool checked);

    [[nodiscard]] QColor alternateColor() const;

    [[nodiscard]] QStringList cleanupRecentAddressEmailList(const QStringList &inputList);

    void setLdapActivitiesAbstract(KLDAPCore::LdapActivitiesAbstract *ldapActivities);

private:
    QStringList mRecentAddressEmailList;
    QStringList mRecentCleanupAddressEmailList;
    mutable QColor mAlternateColor;
    bool mShowOU = false;
    bool mAutoGroupExpand = false;
    KMailCompletion *const mCompletion;
    AddresseeLineEditAkonadi *const mAddresseeLineEditAkonadi;
    AddresseeLineEditLdap *const mAddressessLineEditLdap;
    AddresseeLineEditAkonadiSearch *const mAddressessLineEditBaloo;
};
}
