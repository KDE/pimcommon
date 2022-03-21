/*
  SPDX-FileCopyrightText: 2015-2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include <KLDAP/LdapClientSearch>
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

    Q_REQUIRED_RESULT bool showOU() const;

    void setIcon(const QIcon &icon, const QString &tooltip);

    Q_REQUIRED_RESULT bool useCompletion() const;
    void setUseCompletion(bool useCompletion);

    Q_REQUIRED_RESULT bool completionInitialized() const;

    Q_REQUIRED_RESULT bool smartPaste() const;
    void setSmartPaste(bool smartPaste);

    Q_REQUIRED_RESULT bool searchExtended() const;
    void setSearchExtended(bool searchExtended);

    Q_REQUIRED_RESULT QString searchString() const;
    void setSearchString(const QString &searchString);

    Q_REQUIRED_RESULT bool enableBalooSearch() const;
    void setEnableBalooSearch(bool enableBalooSearch);

    Q_REQUIRED_RESULT bool useSemicolonAsSeparator() const;
    void setUseSemicolonAsSeparator(bool useSemicolonAsSeparator);

    Q_REQUIRED_RESULT bool enableAkonadiSearch() const;
    void setEnableAkonadiSearch(bool enableAkonadiSearch);

    void removeCompletionSource(const QString &source);
    Q_REQUIRED_RESULT int addCompletionSource(const QString &source, int weight);
    void restartTime(const QString &searchString);
    void updateBalooBlackList();
    void updateCompletionOrder();

    KLDAP::LdapClientSearch *ldapSearch();

    void setExpandIntern(bool);
    Q_REQUIRED_RESULT bool expandIntern() const;

    Q_REQUIRED_RESULT bool autoGroupExpand() const;
    void setAutoGroupExpand(bool autoGroupExpand);

    QList<KJob *> mightBeGroupJobs() const;
    void setMightBeGroupJobs(const QList<KJob *> &mightBeGroupJobs);

    Q_REQUIRED_RESULT KContacts::ContactGroup::List groups() const;
    void setGroups(const KContacts::ContactGroup::List &groups);

    void mightBeGroupJobsClear();
    void groupsClear();
    void addGroups(const KContacts::ContactGroup::List &lst);
    void mightBeGroupJobsRemoveOne(Akonadi::ContactGroupSearchJob *search);
    void mightBeGroupJobsAdd(Akonadi::ContactGroupSearchJob *job);
    Q_REQUIRED_RESULT bool groupsIsEmpty() const;
    void setShowRecentAddresses(bool b);
    Q_REQUIRED_RESULT bool showRecentAddresses() const;
    void setRecentAddressConfig(KConfig *config);

    KConfig *recentAddressConfig() const;

    Q_REQUIRED_RESULT bool canDeleteLineEdit() const;
    void setCanDeleteLineEdit(bool inprogressToConfigureCompletion);

public Q_SLOTS:
    void slotToggleExpandGroups(bool);
    void slotShowOUChanged(bool);

private Q_SLOTS:
    void slotCompletion();
    void slotPopupCompletion(const QString &);
    void slotReturnPressed(const QString &);
    void slotStartLDAPLookup();
    void slotLDAPSearchData(const KLDAP::LdapResult::List &);
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
    QTimer *mDelayedQueryTimer = nullptr;
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
