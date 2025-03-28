/*
   SPDX-FileCopyrightText: 2017-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "addresseelineeditldap.h"
#include "addresseelineeditmanager.h"
#include <KLDAPCore/LdapActivitiesAbstract>
#include <KLDAPCore/LdapClient>
#include <KLDAPCore/LdapClientSearch>
#include <KLDAPCore/LdapServer>
#include <KLocalizedString>
#include <QTimer>
#include <chrono>

using namespace std::chrono_literals;
using namespace PimCommon;

AddresseeLineEditLdap::AddresseeLineEditLdap(AddresseeLineEditManager *addressLineStatic, QObject *parent)
    : QObject(parent)
    , mAddressLineStatic(addressLineStatic)
{
}

AddresseeLineEditLdap::~AddresseeLineEditLdap() = default;

void AddresseeLineEditLdap::setLdapActivitiesAbstract(KLDAPCore::LdapActivitiesAbstract *ldapActivities)
{
    if (mLdapActivities != ldapActivities) {
        mLdapActivities = ldapActivities;
        connect(mLdapActivities, &KLDAPCore::LdapActivitiesAbstract::activitiesChanged, this, &AddresseeLineEditLdap::updateLDAPWeights);
        updateLDAPWeights();
    }
}

void AddresseeLineEditLdap::updateLDAPWeights()
{
    /* Add completion sources for all ldap server, 0 to n. Added first so
     * that they map to the LdapClient::clientNumber() */
    mLdapSearch->updateCompletionWeights();
    int clientIndex = 0;
    const QList<KLDAPCore::LdapClient *> lstClients = mLdapSearch->clients();
    for (const KLDAPCore::LdapClient *client : lstClients) {
        if (mLdapActivities) {
            if (mLdapActivities->hasActivitySupport()) {
                if (client->server().enablePlasmaActivities() && !client->server().activities().contains(mLdapActivities->currentActivity())) {
                    continue;
                }
            }
        }
        const int sourceIndex = mAddressLineStatic->addCompletionSource(i18n("LDAP server: %1", client->server().host()), client->completionWeight());
        mLdapClientToCompletionSourceMap.insert(clientIndex, sourceIndex);
        ++clientIndex;
    }
}

QMap<int, int> AddresseeLineEditLdap::ldapClientToCompletionSourceMap() const
{
    return mLdapClientToCompletionSourceMap;
}

int AddresseeLineEditLdap::ldapClientToCompletionSourceValue(int value) const
{
    return mLdapClientToCompletionSourceMap[value];
}

bool AddresseeLineEditLdap::isLdapClientToCompletionSourceMapContains(int value) const
{
    return mLdapClientToCompletionSourceMap.contains(value);
}

KLDAPCore::LdapClientSearch *AddresseeLineEditLdap::ldapSearch() const
{
    return mLdapSearch;
}

void AddresseeLineEditLdap::init()
{
    if (!mLdapTimer) {
        mLdapTimer = new QTimer(this);
        mLdapSearch = new KLDAPCore::LdapClientSearch(this);

        /* The reasoning behind this filter is:
         * If it's a person, or a distlist, show it, even if it doesn't have an email address.
         * If it's not a person, or a distlist, only show it if it has an email attribute.
         * This allows both resource accounts with an email address which are not a person and
         * person entries without an email address to show up, while still not showing things
         * like structural entries in the ldap tree.
         */

#if 0
        mLdapSearch->setFilter(QStringLiteral("&(|(objectclass=person)(objectclass=groupOfNames)(mail=*))"
                                              "(|(cn=%1*)(mail=%1*)(mail=*@%1*)(givenName=%1*)(sn=%1*))"));
#endif
        // Fix bug 323272 "Exchange doesn't like any queries beginning with *."
        mLdapSearch->setFilter(
            QStringLiteral("&(|(objectclass=person)(objectclass=groupOfNames)(mail=*))"
                           "(|(cn=%1*)(mail=%1*)(givenName=%1*)(sn=%1*))"));
    }
}

QTimer *AddresseeLineEditLdap::ldapTimer() const
{
    return mLdapTimer;
}

QString AddresseeLineEditLdap::ldapText() const
{
    return mLdapText;
}

void AddresseeLineEditLdap::setLdapText(const QString &ldapText)
{
    mLdapText = ldapText;
}

AddresseeLineEdit *AddresseeLineEditLdap::addressLineEdit() const
{
    return mAddressLineEdit;
}

void AddresseeLineEditLdap::setAddressLineEdit(AddresseeLineEdit *addressLineEdit)
{
    mAddressLineEdit = addressLineEdit;
}

void AddresseeLineEditLdap::startLoadingLDAPEntries()
{
    QString text(mLdapText);

    const int index = text.lastIndexOf(QLatin1Char(','));
    if (index >= 0) {
        text = text.mid(index + 1, 255).trimmed();
    }

    if (text.isEmpty()) {
        return;
    }

    mLdapSearch->startSearch(text);
}

void AddresseeLineEditLdap::restartLdap(const QString &searchString, AddresseeLineEdit *addressLine)
{
    if (mLdapTimer) {
        if (mLdapText != searchString || mAddressLineEdit != addressLine) {
            stopLDAPLookup();
        }

        mLdapText = searchString;
        mAddressLineEdit = addressLine;
        mLdapTimer->setSingleShot(true);
        mLdapTimer->start(500ms);
    }
}

void AddresseeLineEditLdap::stopLDAPLookup()
{
    if (mLdapSearch) {
        mLdapSearch->cancelSearch();
        setAddressLineEdit(nullptr);
    }
}
