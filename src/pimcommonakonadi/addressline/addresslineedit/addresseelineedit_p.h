/*
  SPDX-FileCopyrightText: 2015-2024 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include <KLDAPWidgets/LdapClientSearch>
#include <QList>
#include <QObject>
#include <QStringList>

#include <Akonadi/Collection>
#include <Akonadi/Item>
#include <KContacts/ContactGroup>

class KConfig;
class QToolButton;
class QTimer;
namespace Akonadi
{
class ContactGroupSearchJob;
}

namespace PimCommon
{
class AddresseeLineEdit;
class AddresseeLineEditPrivate : public QObject
{
    Q_OBJECT
public:
    AddresseeLineEditPrivate(AddresseeLineEdit *qq, bool enableCompletion);
    ~AddresseeLineEditPrivate() override;
    void init();
    void setCompletedItems(const QStringList &items, bool autoSuggest);
    void addCompletionItem(const QString &string, int weight, int source, const QStringList *keyWords = nullptr);
    const QStringList adjustedCompletionItems(bool fullSearch);
    void updateSearchString();
    void startSearches();
    void akonadiPerformSearch();
    void akonadiHandlePending();
    void doCompletion(bool ctrlT);

    [[nodiscard]] bool showOU() const;

    void setIcon(const QIcon &icon, const QString &tooltip);

    [[nodiscard]] bool useCompletion() const;
    void setUseCompletion(bool useCompletion);

    [[nodiscard]] bool completionInitialized() const;

    [[nodiscard]] bool smartPaste() const;
    void setSmartPaste(bool smartPaste);

    [[nodiscard]] bool searchExtended() const;
    void setSearchExtended(bool searchExtended);

    [[nodiscard]] QString searchString() const;
    void setSearchString(const QString &searchString);

    [[nodiscard]] bool enableBalooSearch() const;
    void setEnableBalooSearch(bool enableBalooSearch);

    [[nodiscard]] bool useSemicolonAsSeparator() const;
    void setUseSemicolonAsSeparator(bool useSemicolonAsSeparator);

    [[nodiscard]] bool enableAkonadiSearch() const;
    void setEnableAkonadiSearch(bool enableAkonadiSearch);

    void removeCompletionSource(const QString &source);
    [[nodiscard]] int addCompletionSource(const QString &source, int weight);
    void restartTime(const QString &searchString);
    void updateBalooBlackList();
    void updateCompletionOrder();

    KLDAPWidgets::LdapClientSearch *ldapSearch();

    void setExpandIntern(bool);
    [[nodiscard]] bool expandIntern() const;

    [[nodiscard]] bool autoGroupExpand() const;
    void setAutoGroupExpand(bool autoGroupExpand);

    QList<KJob *> mightBeGroupJobs() const;
    void setMightBeGroupJobs(const QList<KJob *> &mightBeGroupJobs);

    [[nodiscard]] KContacts::ContactGroup::List groups() const;
    void setGroups(const KContacts::ContactGroup::List &groups);

    void mightBeGroupJobsClear();
    void groupsClear();
    void addGroups(const KContacts::ContactGroup::List &lst);
    void mightBeGroupJobsRemoveOne(Akonadi::ContactGroupSearchJob *search);
    void mightBeGroupJobsAdd(Akonadi::ContactGroupSearchJob *job);
    [[nodiscard]] bool groupsIsEmpty() const;
    void setShowRecentAddresses(bool b);
    [[nodiscard]] bool showRecentAddresses() const;
    void setRecentAddressConfig(KConfig *config);

    KConfig *recentAddressConfig() const;

    [[nodiscard]] bool canDeleteLineEdit() const;
    void setCanDeleteLineEdit(bool inprogressToConfigureCompletion);

public Q_SLOTS:
    void slotToggleExpandGroups(bool);
    void slotShowOUChanged(bool);

private Q_SLOTS:
    void slotCompletion();
    void slotPopupCompletion(const QString &);
    void slotReturnPressed(const QString &);
    void slotStartLDAPLookup();
    void slotLDAPSearchData(const KLDAPWidgets::LdapResult::List &);
    void slotEditCompletionOrder();
    void slotUserCancelled(const QString &);
    void slotAkonadiHandleItems(const Akonadi::Item::List &items);
    void slotAkonadiSearchResult(KJob *);
    void slotAkonadiCollectionsReceived(const Akonadi::Collection::List &);
    void searchInBaloo();
    void slotTriggerDelayedQueries();

private:
    AddresseeLineEdit *const q;
    QToolButton *mToolButton = nullptr;
    QTimer *const mDelayedQueryTimer;
    QString mPreviousAddresses;
    QString mSearchString;
    QList<KJob *> mMightBeGroupJobs;
    KContacts::ContactGroup::List mGroups;
    KConfig *mRecentAddressConfig = nullptr;
    bool mUseCompletion = false;
    bool mCompletionInitialized = false;
    bool mSmartPaste = false;
    bool mLastSearchMode = false;
    bool mSearchExtended = false; // has \" been added?
    bool mUseSemicolonAsSeparator = false;
    bool mEnableBalooSearch = true;
    bool mEnableAkonadiSearch = true;
    bool mExpandIntern = true;
    bool mShowRecentAddresses = true;
    bool mCanDeleteLineEdit = true;
};
}
