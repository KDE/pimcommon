/*
  This file is part of libkdepim.

  SPDX-FileCopyrightText: 2002 Helge Deller <deller@gmx.de>
  SPDX-FileCopyrightText: 2002 Lubos Lunak <llunak@suse.cz>
  SPDX-FileCopyrightText: 2001, 2003 Carsten Pfeiffer <pfeiffer@kde.org>
  SPDX-FileCopyrightText: 2001 Waldo Bastian <bastian@kde.org>
  SPDX-FileCopyrightText: 2004 Daniel Molkentin <danimo@klaralvdalens-datakonsult.se>
  SPDX-FileCopyrightText: 2004 Karl-Heinz Zimmer <khz@klaralvdalens-datakonsult.se>
  SPDX-FileCopyrightText: 2017-2022 Laurent Montel <montel@kde.org>

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
class QObject;
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
namespace KLDAP
{
class LdapClientSearch;
}

namespace PimCommon
{
class AddresseeLineEditPrivate;
class PIMCOMMONAKONADI_EXPORT AddresseeLineEdit : public KLineEdit
{
    Q_OBJECT

public:
    /**
     * Creates a new addressee line edit.
     *
     * @param parent The parent object.
     * @param enableCompletion Whether autocompletion shall be enabled.
     */
    explicit AddresseeLineEdit(QWidget *parent = nullptr, bool enableCompletion = true);

    /**
     * Destroys the addressee line edit.
     */
    ~AddresseeLineEdit() override;

    /**
     * Sets whether semicolons are allowed as separators.
     */
    void allowSemicolonAsSeparator(bool allow);

    /**
     * Reimplemented for setting the @p font for line edit and completion box.
     */
    void setFont(const QFont &font);

    void setEnableBalooSearch(bool enable);
    Q_REQUIRED_RESULT bool enableBalooSearch() const;

    void setEnableAkonadiSearch(bool enable);
    Q_REQUIRED_RESULT bool enableAkonadiSearch() const;

    void setExpandIntern(bool);
    Q_REQUIRED_RESULT bool expandIntern() const;

    Q_REQUIRED_RESULT bool isCompletionEnabled() const;

    /**
     * Adds a new @p contact to the completion with a given
     * @p weight
     * @p source index
     * @p append  is added to completion string, but removed, when mail is selected.
     */
    void addContact(const KContacts::Addressee &contact, int weight, int source = -1, const QString &append = QString());

    /**
     * Same as the above, but this time with contact groups.
     */
    void addContactGroup(const KContacts::ContactGroup &group, int weight, int source = -1);

    void addItem(const Akonadi::Item &item, int weight, int source = -1);

    /**
     * Adds the @p name of a completion source and its @p weight
     * to the internal list of completion sources and returns its index,
     * which can be used for insertion of items associated with that source.
     *
     * If the source already exists, the weight will be updated.
     */
    Q_REQUIRED_RESULT int addCompletionSource(const QString &name, int weight);

    void removeCompletionSource(const QString &source);
    void emitTextCompleted();

    void callUserCancelled(const QString &str);
    void callSetCompletedText(const QString & /*text*/, bool /*marked*/);
    void callSetCompletedText(const QString &text);
    void callSetUserSelection(bool);

    void updateBalooBlackList();
    void updateCompletionOrder();
    Q_REQUIRED_RESULT KLDAP::LdapClientSearch *ldapSearch() const;

    void setShowRecentAddresses(bool b);
    Q_REQUIRED_RESULT bool showRecentAddresses() const;

    void setRecentAddressConfig(KConfig *config);
    Q_REQUIRED_RESULT KConfig *recentAddressConfig() const;

    void configureCompletion();

    void setIcon(const QIcon &icon, const QString &tooltip = QString());

    Q_REQUIRED_RESULT bool canDeleteLineEdit() const;
Q_SIGNALS:
    void textCompleted();
    void addAddress(const QString &address);
    void iconClicked();

public Q_SLOTS:
    /**
     * Moves the cursor at the end of the line edit.
     */
    void cursorAtEnd();

    /**
     * Sets whether autocompletion shall be enabled.
     */
    void enableCompletion(bool enable);

    /**
     * Reimplemented for stripping whitespace after completion
     * Danger: This is _not_ virtual in the base class!
     */
    void setText(const QString &text) override;

    void expandGroups();
    void slotEditingFinished();
    void slotGroupSearchResult(KJob *job);

protected:
    /**
     * Reimplemented for smart insertion of email addresses.
     * Features:
     * - Automatically adds ',' if necessary to separate email addresses
     * - Correctly decodes mailto URLs
     * - Recognizes email addresses which are protected against address
     *   harvesters, i.e. "name at kde dot org" and "name(at)kde.org"
     */
    virtual void insert(const QString &);

    /**
     * Reimplemented for smart insertion of pasted email addresses.
     */
    virtual void paste();

    /**
     * Reimplemented for smart insertion with middle mouse button.
     */
    void mouseReleaseEvent(QMouseEvent *) override;

#ifndef QT_NO_DRAGANDDROP
    /**
     * Reimplemented for smart insertion of dragged email addresses.
     */
    void dropEvent(QDropEvent *) override;
#endif

    /**
     * Reimplemented for internal reasons.
     */
    void keyPressEvent(QKeyEvent *) override;

#ifndef QT_NO_CONTEXTMENU
    /**
     * Reimplemented for subclass access to menu
     */
    virtual QMenu *createStandardContextMenu();

    /**
     * Reimplemented for internal reasons.  API not affected.
     *
     * See QLineEdit::contextMenuEvent().
     */
    void contextMenuEvent(QContextMenuEvent *) override;
#endif

    void insertEmails(const QStringList &emails);
    void loadContacts();

private:
    void addContact(const QStringList &emails, const KContacts::Addressee &addr, int weight, int source, QString append = QString());
    void groupExpandResult(KJob *job);
    bool eventFilter(QObject *, QEvent *) override;

    AddresseeLineEditPrivate *const d;
};
}
