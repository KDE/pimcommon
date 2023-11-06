/*
 *
 *  SPDX-FileCopyrightText: 2001-2003 Carsten Pfeiffer <pfeiffer@kde.org>
 *  SPDX-FileCopyrightText: 2003 Zack Rusin <zack@kde.org>
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 */
#include "recentaddresses.h"

#include <KConfig>
#include <KConfigGroup>
#include <KEmailAddress>
#include <KSharedConfig>
#include <QCoreApplication>

using namespace PimCommon;

RecentAddresses *s_self = nullptr;

void deleteGlobalRecentAddresses()
{
    delete s_self;
    s_self = nullptr;
}

RecentAddresses *RecentAddresses::self(KConfig *config)
{
    if (!s_self) {
        s_self = new RecentAddresses(config);
        qAddPostRoutine(deleteGlobalRecentAddresses);
    }
    return s_self;
}

bool RecentAddresses::exists()
{
    return s_self != nullptr;
}

RecentAddresses::RecentAddresses(KConfig *config)
{
    if (config) {
        load(config);
    } else {
        load(KSharedConfig::openConfig().data());
    }
}

RecentAddresses::~RecentAddresses() = default;

void RecentAddresses::load(KConfig *config)
{
    QString name;
    QString emailString;

    m_addresseeList.clear();
    KConfigGroup cg(config, QLatin1String("General"));
    m_maxCount = cg.readEntry("Maximum Recent Addresses", 200);
    const QStringList addresses = cg.readEntry("Recent Addresses", QStringList());
    for (const QString &address : addresses) {
        KContacts::Addressee::parseEmailAddress(address, name, emailString);
        if (!emailString.isEmpty()) {
            KContacts::Addressee addr;
            addr.setNameFromString(name);
            KContacts::Email email(emailString);
            email.setPreferred(true);
            addr.addEmail(email);
            m_addresseeList.append(addr);
        }
    }

    adjustSize();
}

void RecentAddresses::save(KConfig *config)
{
    KConfigGroup cg(config, QLatin1String("General"));
    cg.writeEntry("Recent Addresses", addresses());
}

void RecentAddresses::add(const QString &entry)
{
    if (!entry.isEmpty() && m_maxCount > 0) {
        const QStringList list = KEmailAddress::splitAddressList(entry);
        for (const QString &str : list) {
            KEmailAddress::EmailParseResult errorCode = KEmailAddress::isValidAddress(str);
            if (errorCode != KEmailAddress::AddressOk) {
                continue;
            }
            QString emailString;
            QString fullName;
            KContacts::Addressee addr;

            KContacts::Addressee::parseEmailAddress(str, fullName, emailString);

            KContacts::Addressee::List::Iterator end(m_addresseeList.end());
            for (KContacts::Addressee::List::Iterator it = m_addresseeList.begin(); it != end; ++it) {
                if (emailString == (*it).preferredEmail()) {
                    // already inside, remove it here and add it later at pos==1
                    m_addresseeList.erase(it);
                    break;
                }
            }
            addr.setNameFromString(fullName);
            KContacts::Email email(emailString);
            email.setPreferred(true);
            addr.addEmail(email);
            m_addresseeList.prepend(addr);
            adjustSize();
        }
    }
}

void RecentAddresses::setMaxCount(int count)
{
    if (count != m_maxCount) {
        m_maxCount = count;
        adjustSize();
    }
}

int RecentAddresses::maxCount() const
{
    return m_maxCount;
}

void RecentAddresses::adjustSize()
{
    while (m_addresseeList.count() > m_maxCount) {
        m_addresseeList.takeLast();
    }
}

void RecentAddresses::clear()
{
    m_addresseeList.clear();
}

QStringList RecentAddresses::addresses() const
{
    QStringList addresses;
    addresses.reserve(m_addresseeList.count());
    for (const KContacts::Addressee &addr : m_addresseeList) {
        addresses.append(addr.fullEmail());
    }
    return addresses;
}
