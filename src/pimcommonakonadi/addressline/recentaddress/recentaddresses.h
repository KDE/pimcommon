/*
 *
 *  SPDX-FileCopyrightText: 2001-2003 Carsten Pfeiffer <pfeiffer@kde.org>
 *  SPDX-FileCopyrightText: 2003 Zack Rusin <zack@kde.org>
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 */
#pragma once

#include "pimcommonakonadi_export.h"
#include <KContacts/Addressee>
#include <QStringList>
class KConfig;

namespace PimCommon
{
/*!
 * \class RecentAddresses
 * \brief The RecentAddresses class handles a list of recent email addresses
 * \inmodule PimCommonAkonadi
 * \inheaderfile PimCommonAkonadi/RecentAddresses
 * \author Carsten Pfeiffer <pfeiffer@kde.org>
 */

class PIMCOMMONAKONADI_EXPORT RecentAddresses
{
public:
    /*!
     * Destructs the RecentAddresses.
     */
    ~RecentAddresses();
    /*!
     * Returns the singleton instance of RecentAddresses.
     * @param config The KConfig to load from
     * @return The singleton instance
     */
    static RecentAddresses *self(KConfig *config = nullptr);

    /*!
     * Checks if the RecentAddresses singleton has been created.
     * @return true if an instance exists, false otherwise
     */
    static bool exists();

    /*!
     * Returns the list of recent addresses.
     * @return A list of email addresses or address groups
     */
    [[nodiscard]] QStringList addresses() const;

    /*!
     * Adds an entry to the list of recent addresses.
     * @param entry The address entry to add
     */
    void add(const QString &entry);

    /*!
     * Sets the maximum number of entries the list can hold.
     * @param count The maximum number of entries (default is 40)
     */
    void setMaxCount(int count);

    /*!
     * Returns the current maximum number of entries.
     * @return The maximum count
     */
    [[nodiscard]] int maxCount() const;

    /*!
     * Loads recent addresses from the configuration file.
     * @param config The KConfig object to load from
     */
    void load(KConfig *);

    /*!
     * Saves recent addresses to the configuration file.
     * @param config The KConfig object to save to
     */
    void save(KConfig *);

    /*!
     * Clears all recent addresses.
     */
    void clear();

private:
    PIMCOMMONAKONADI_NO_EXPORT explicit RecentAddresses(KConfig *config = nullptr);
    PIMCOMMONAKONADI_NO_EXPORT void adjustSize();

    KContacts::Addressee::List m_addresseeList;

    int m_maxCount;
};
}
