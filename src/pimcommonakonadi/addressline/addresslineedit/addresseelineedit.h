/*
  This file is part of libkdepim.

  SPDX-FileCopyrightText: 2002 Helge Deller <deller@gmx.de>
  SPDX-FileCopyrightText: 2002 Lubos Lunak <llunak@suse.cz>
  SPDX-FileCopyrightText: 2001, 2003 Carsten Pfeiffer <pfeiffer@kde.org>
  SPDX-FileCopyrightText: 2001 Waldo Bastian <bastian@kde.org>
  SPDX-FileCopyrightText: 2004 Daniel Molkentin <danimo@klaralvdalens-datakonsult.se>
  SPDX-FileCopyrightText: 2004 Karl-Heinz Zimmer <khz@klaralvdalens-datakonsult.se>
  SPDX-FileCopyrightText: 2017-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "pimcommonakonadi_export.h"

#include <KLineEdit>

class QDropEvent;
class QEvent;
class QKeyEvent;
class QMenu;
class QMouseEvent;
class KJob;
class KConfig;
namespace Akonadi
{
class Item;
}

namespace KContacts
{
class Addressee;
class ContactGroup;
}
namespace KLDAPCore
{
class LdapClientSearch;
class LdapActivitiesAbstract;
}

namespace PimCommon
{
class AddresseeLineEditPrivate;
/*!
 * \class PimCommon::AddresseeLineEdit
 * \brief The AddresseeLineEdit class provides a line editor for entering email addresses with completion support
 * \inmodule PimCommonAkonadi
 * \inheaderfile PimCommonAkonadi/AddresseeLineEdit
 * \author Helge Deller <deller@gmx.de>
 */
class PIMCOMMONAKONADI_EXPORT AddresseeLineEdit : public KLineEdit
{
    Q_OBJECT

public:
    /*!
     * Creates a new addressee line edit.
     *
     * \a parent The parent object.
     * \a enableCompletion Whether autocompletion shall be enabled.
     */
    explicit AddresseeLineEdit(QWidget *parent = nullptr, bool enableCompletion = true);

    /*!
     * Destroys the addressee line edit.
     */
    ~AddresseeLineEdit() override;

    /*!
     * Sets whether semicolons are allowed as separators.
     */
    void allowSemicolonAsSeparator(bool allow);

    /*!
     * Reimplemented for setting the \a font for line edit and completion box.
     */
    void setFont(const QFont &font);

    void setEnableBalooSearch(bool enable);
    [[nodiscard]] bool enableBalooSearch() const;

    void setEnableAkonadiSearch(bool enable);
    [[nodiscard]] bool enableAkonadiSearch() const;

    void setExpandIntern(bool);
    [[nodiscard]] bool expandIntern() const;

    [[nodiscard]] bool isCompletionEnabled() const;

    /*!
     * Adds a new \a contact to the completion with a given
     * \a weight
     * \a source index
     * \a append  is added to completion string, but removed, when mail is selected.
     */
    void addContact(const KContacts::Addressee &contact, int weight, int source = -1, const QString &append = QString());

    /*!
     * Same as the above, but this time with contact groups.
     */
    void addContactGroup(const KContacts::ContactGroup &group, int weight, int source = -1);

    /*!
     * Adds an Akonadi item to the completion list.
     * @param item The Akonadi item to add
     * @param weight The weight for completion priority
     * @param source The source index for this item
     */
    void addItem(const Akonadi::Item &item, int weight, int source = -1);

    /*!
     * Adds the \a name of a completion source and its \a weight
     * to the internal list of completion sources and returns its index,
     * which can be used for insertion of items associated with that source.
     *
     * If the source already exists, the weight will be updated.
     */
    [[nodiscard]] int addCompletionSource(const QString &name, int weight);

    /*!
     * Removes a completion source.
     * @param source The name of the source to remove
     */
    void removeCompletionSource(const QString &source);
    /*!
     * Emits the textCompleted signal.
     */
    void emitTextCompleted();

    /*!
     * Calls user cancelled callback with the given string.
     * @param str The cancelled input string
     */
    void callUserCancelled(const QString &str);
    /*!
     * Sets the completed text.
     * @param text The completed text
     * @param marked Whether the completion should be marked
     */
    void callSetCompletedText(const QString & /*text*/, bool /*marked*/);
    /*!
     * Sets the completed text.
     * @param text The completed text
     */
    void callSetCompletedText(const QString &text);
    /*!
     * Sets user selection state.
     * @param selected Whether user made a selection
     */
    void callSetUserSelection(bool);

    /*!
     * Updates the Baloo blacklist.
     */
    void updateBalooBlackList();
    /*!
     * Updates the completion order.
     */
    void updateCompletionOrder();
    /*!
     * Returns the LDAP search client.
     * @return The LdapClientSearch instance
     */
    [[nodiscard]] KLDAPCore::LdapClientSearch *ldapSearch() const;

    /*!
     * Sets whether to show recent addresses.
     * @param b true to show recent addresses, false otherwise
     */
    void setShowRecentAddresses(bool b);
    /*!
     * Returns whether recent addresses are shown.
     * @return true if recent addresses are shown
     */
    [[nodiscard]] bool showRecentAddresses() const;

    /*!
     * Sets the KConfig object for recent addresses.
     * @param config The KConfig object
     */
    void setRecentAddressConfig(KConfig *config);
    /*!
     * Returns the KConfig object for recent addresses.
     * @return The KConfig object
     */
    [[nodiscard]] KConfig *recentAddressConfig() const;

    /*!
     * Opens the configuration dialog for address completion.
     */
    void configureCompletion();

    /*!
     * Sets an icon with tooltip for this line edit.
     * @param icon The icon to display
     * @param tooltip The tooltip text
     */
    void setIcon(const QIcon &icon, const QString &tooltip = QString());

    /*!
     * Checks if this line edit can be deleted.
     * @return true if it can be deleted, false otherwise
     */
    [[nodiscard]] bool canDeleteLineEdit() const;
    /*!
     * Sets the LDAP activities abstract object.
     * @param ldapActivities The LdapActivitiesAbstract instance
     */
    void setLdapActivitiesAbstract(KLDAPCore::LdapActivitiesAbstract *ldapActivities);
Q_SIGNALS:
    /*!
     * Emitted when text completion is requested.
     */
    void textCompleted();
    /*!
     * Emitted when an address should be added.
     * @param address The address to add
     */
    void addAddress(const QString &address);
    /*!
     * Emitted when the icon is clicked.
     */
    void iconClicked();

public Q_SLOTS:
    /*!
     * Moves the cursor at the end of the line edit.
     */
    void cursorAtEnd();

    /*!
     * Sets whether autocompletion shall be enabled.
     * @param enable true to enable completion, false to disable
     */
    void enableCompletion(bool enable);

    /*!
     * Reimplemented for stripping whitespace after completion
     * Danger: This is _not_ virtual in the base class!
     * @param text The text to set
     */
    void setText(const QString &text) override;

    /*!
     * Expands contact groups to individual addresses.
     */
    void expandGroups();
    /*!
     * Called when editing is finished.
     */
    void slotEditingFinished();
    /*!
     * Handles group search results.
     * @param job The KJob with search results
     */
    void slotGroupSearchResult(KJob *job);

protected:
    /*!
     * Reimplemented for smart insertion of email addresses.
     * Features:
     * - Automatically adds ',' if necessary to separate email addresses
     * - Correctly decodes mailto URLs
     * - Recognizes email addresses which are protected against address
     *   harvesters, i.e. "name at kde dot org" and "name(at)kde.org"
     * @param text The text to insert
     */
    virtual void insert(const QString &);

    /*!
     * Reimplemented for smart insertion of pasted email addresses.
     */
    virtual void paste();

    /*!
     * Reimplemented for smart insertion with middle mouse button.
     * @param event The mouse event
     */
    void mouseReleaseEvent(QMouseEvent *) override;

    /*!
     * Reimplemented for smart insertion of dragged email addresses.
     * @param event The drop event
     */
    void dropEvent(QDropEvent *) override;

    /*!
     * Reimplemented for internal reasons.
     * @param event The key event
     */
    void keyPressEvent(QKeyEvent *) override;

    /*!
     * Reimplemented for subclass access to menu.
     * @return The standard context menu
     */
    virtual QMenu *createStandardContextMenu();

    /*!
     * Reimplemented for internal reasons. API not affected.
     * @param event The context menu event
     */
    void contextMenuEvent(QContextMenuEvent *) override;

    /*!
     * Inserts multiple email addresses.
     * @param emails The list of email addresses to insert
     */
    void insertEmails(const QStringList &emails);
    /*!
     * Loads contacts into the completion list.
     */
    void loadContacts();

private:
    PIMCOMMONAKONADI_NO_EXPORT void addContact(const QStringList &emails, const KContacts::Addressee &addr, int weight, int source, QString append = QString());
    PIMCOMMONAKONADI_NO_EXPORT void groupExpandResult(KJob *job);
    bool eventFilter(QObject *, QEvent *) override;

    AddresseeLineEditPrivate *const d;
};
}
