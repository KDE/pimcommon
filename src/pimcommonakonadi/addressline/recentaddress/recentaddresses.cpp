/*
 *
 *  Copyright (c) 2001-2003 Carsten Pfeiffer <pfeiffer@kde.org>
 *  Copyright (c) 2003 Zack Rusin <zack@kde.org>
 *
 *  KMail is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  KMail is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 *  In addition, as a special exception, the copyright holders give
 *  permission to link the code of this program with any edition of
 *  the Qt library by Trolltech AS, Norway (or with modified versions
 *  of Qt that use the same license as Qt), and distribute linked
 *  combinations including the two.  You must obey the GNU General
 *  Public License in all respects for all of the code used other than
 *  Qt.  If you modify this file, you may extend this exception to
 *  your version of the file, but you are not obligated to do so.  If
 *  you do not wish to do so, delete this exception statement from
 *  your version.
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
    if (config) {
        load(config);
    } else {
        load(KSharedConfig::openConfig().data());
    }
}

RecentAddresses::~RecentAddresses()
{
}

void RecentAddresses::load(KConfig *config)
{
    QString name;
    QString email;

    m_addresseeList.clear();
    KConfigGroup cg(config, "General");
    m_maxCount = cg.readEntry("Maximum Recent Addresses", 200);
    const QStringList addresses = cg.readEntry("Recent Addresses", QStringList());
    for (const QString &address : addresses ) {
        KContacts::Addressee::parseEmailAddress(address, name, email);
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
        for (const QString &str : list) {
            KEmailAddress::EmailParseResult errorCode = KEmailAddress::isValidAddress(str);
            if (errorCode != KEmailAddress::AddressOk) {
                continue;
            }
            QString email;
            QString fullName;
            KContacts::Addressee addr;

            KContacts::Addressee::parseEmailAddress(str, fullName, email);

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
    for (const KContacts::Addressee &addr : m_addresseeList) {
        addresses.append(addr.fullEmail());
    }
    return addresses;
}
