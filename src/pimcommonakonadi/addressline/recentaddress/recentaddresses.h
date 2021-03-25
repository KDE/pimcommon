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
/**
 * Handles a list of "recent email-addresses". Simply set a max-count and
 * call @ref add() to add entries.
 *
 * @author Carsten Pfeiffer <pfeiffer@kde.org>
 */

class PIMCOMMONAKONADI_EXPORT RecentAddresses
{
public:
    ~RecentAddresses();
    /**
     * @returns the only possible instance of this class.
     */
    static RecentAddresses *self(KConfig *config = nullptr);

    /*
     * @return true if self() was called, i.e. a RecentAddresses instance exists
     */
    static bool exists();

    /**
     * @returns the list of recent addresses.
     * Note: an entry doesn't have to be one email address, it can be multiple,
     * like "Foo <foo@bar.org>, Bar Baz <bar@baz.org>".
     */
    Q_REQUIRED_RESULT QStringList addresses() const;

    /**
     * Adds an entry to the list.
     * Note: an entry doesn't have to be one email address, it can be multiple,
     * like "Foo <foo@bar.org>, Bar Baz <bar@baz.org>".
     */
    void add(const QString &entry);

    /**
     * Sets the maximum number, the list can hold. The list adjusts to this
     * size if necessary. Default maximum is 40.
     */
    void setMaxCount(int count);

    /**
     * @returns the current maximum number of entries.
     */
    Q_REQUIRED_RESULT int maxCount() const;

    /**
     * Loads the list of recently used addresses from the configfile.
     * Automatically done on startup.
     */
    void load(KConfig *);

    /**
     * Saves the list of recently used addresses to the configfile.
     * Make sure to call KSharedConfig::openConfig()->sync() afterwards, to really save.
     */
    void save(KConfig *);

    /**
     * Removes all entries from the history.
     */
    void clear();

private:
    explicit RecentAddresses(KConfig *config = nullptr);
    void adjustSize();

    KContacts::Addressee::List m_addresseeList;

    int m_maxCount;
};
}

