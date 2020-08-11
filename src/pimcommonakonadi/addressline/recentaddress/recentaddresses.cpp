/*
 *
 *  SPDX-FileCopyrightText: 2001-2003 Carsten Pfeiffer <pfeiffer@kde.org>
 *  SPDX-FileCopyrightText: 2003 Zack Rusin <zack@kde.org>
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 */
#include "recentaddresses.h"

#include <KEmailAddress>
#include <KConfig>
#include <KConfigGroup>
#include "pimcommonakonadi_debug.h"
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
    if (!config) {
        load(KSharedConfig::openConfig().data());
    } else {
        load(config);
    }
}

RecentAddresses::~RecentAddresses()
{
}

void RecentAddresses::load(KConfig *config)
{
    QStringList addresses;
    QString name;
    QString email;

    m_addresseeList.clear();
    KConfigGroup cg(config, "General");
    m_maxCount = cg.readEntry("Maximum Recent Addresses", 200);
    addresses = cg.readEntry("Recent Addresses", QStringList());
    QStringList::ConstIterator end(addresses.constEnd());
    for (QStringList::ConstIterator it = addresses.constBegin(); it != end; ++it) {
        KContacts::Addressee::parseEmailAddress(*it, name, email);
        if (!email.isEmpty()) {
            KContacts::Addressee addr;
            addr.setNameFromString(name);
            addr.insertEmail(email, true);
            m_addresseeList.append(addr);
        }
    }

    adjustSize();
}

void RecentAddresses::save(KConfig *config)
{
    KConfigGroup cg(config, "General");
    cg.writeEntry("Recent Addresses", addresses());
}

void RecentAddresses::add(const QString &entry)
{
    if (!entry.isEmpty() && m_maxCount > 0) {
        const QStringList list = KEmailAddress::splitAddressList(entry);
        QStringList::const_iterator e_itEnd(list.constEnd());
        for (QStringList::const_iterator e_it = list.constBegin(); e_it != e_itEnd; ++e_it) {
            KEmailAddress::EmailParseResult errorCode = KEmailAddress::isValidAddress(*e_it);
            if (errorCode != KEmailAddress::AddressOk) {
                continue;
            }
            QString email;
            QString fullName;
            KContacts::Addressee addr;

            KContacts::Addressee::parseEmailAddress(*e_it, fullName, email);

            KContacts::Addressee::List::Iterator end(m_addresseeList.end());
            for (KContacts::Addressee::List::Iterator it = m_addresseeList.begin();
                 it != end; ++it) {
                if (email == (*it).preferredEmail()) {
                    //already inside, remove it here and add it later at pos==1
                    m_addresseeList.erase(it);
                    break;
                }
            }
            addr.setNameFromString(fullName);
            addr.insertEmail(email, true);
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
    KContacts::Addressee::List::ConstIterator end = m_addresseeList.constEnd();
    for (KContacts::Addressee::List::ConstIterator it = m_addresseeList.constBegin();
         it != end; ++it) {
        addresses.append((*it).fullEmail());
    }
    return addresses;
}
