/*
 * This file is part of libkldap.
 *
 * SPDX-FileCopyrightText: 2002 Klarälvdalens Datakonsult AB
 * SPDX-FileContributor: Steffen Hansen <hansen@kde.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 */
#pragma once

#include "pimcommonakonadi_export.h"

#include <KContacts/Addressee>
#include <QDialog>

class QCloseEvent;

namespace KLDAPCore
{
class LdapClient;
class LdapObject;
}
namespace PimCommon
{
/*!
 * \class PimCommon::LdapSearchDialog
 * \brief The LdapSearchDialog class provides a dialog for searching contacts in LDAP directories
 * \inmodule PimCommonAkonadi
 * \inheaderfile PimCommonAkonadi/LdapSearchDialog
 * \author Steffen Hansen <hansen@kde.org>
 */
class PIMCOMMONAKONADI_EXPORT LdapSearchDialog : public QDialog
{
    Q_OBJECT

public:
    enum class FilterType : uint8_t {
        Name = 0,
        Email,
        HomeNumber,
        WorkNumber,
    };

    /*!
     * Constructs a new LDAP search dialog.
     * @param parent The parent widget
     */
    explicit LdapSearchDialog(QWidget *parent = nullptr);

    /*!
     * Destructs the LDAP search dialog.
     */
    ~LdapSearchDialog() override;

    /*!
     * Sets the search text in the search line edit.
     * @param text The text to search for
     */
    void setSearchText(const QString &text);

    /*!
     * Returns the list of contacts selected in the LDAP search.
     * @return A list of selected KContacts::Addressee objects
     */
    KContacts::Addressee::List selectedContacts() const;

Q_SIGNALS:
    /*!
     * Emitted when the user clicks the 'Add Selected' button.
     */
    void contactsAdded();

protected Q_SLOTS:
    void slotUser1();
    void slotUser2();
    void slotCustomContextMenuRequested(const QPoint &);
    void slotCancelClicked();

protected:
    void closeEvent(QCloseEvent *) override;

private:
    class LdapSearchDialogPrivate;
    std::unique_ptr<LdapSearchDialogPrivate> const d;

    Q_PRIVATE_SLOT(d, void slotAddResult(const KLDAPCore::LdapClient &, const KLDAPCore::LdapObject &))
    Q_PRIVATE_SLOT(d, void slotStartSearch())
    Q_PRIVATE_SLOT(d, void slotStopSearch())
    Q_PRIVATE_SLOT(d, void slotSearchDone())
};
}
Q_DECLARE_METATYPE(PimCommon::LdapSearchDialog::FilterType)
