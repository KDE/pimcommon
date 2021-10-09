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

namespace KLDAP
{
class LdapClient;
class LdapObject;
}
namespace PimCommon
{
/**
 * @short A dialog to search contacts in a LDAP directory.
 *
 * This dialog allows the user to search for contacts inside
 * a LDAP directory.
 *
 * @author Steffen Hansen <hansen@kde.org>
 * @since 4.5
 */
class PIMCOMMONAKONADI_EXPORT LdapSearchDialog : public QDialog
{
    Q_OBJECT

public:
    enum FilterType { Name = 0, Email, HomeNumber, WorkNumber };

    /**
     * Creates a new ldap search dialog.
     *
     * @param parent The parent widget.
     */
    explicit LdapSearchDialog(QWidget *parent = nullptr);

    /**
     * Destroys the ldap search dialog.
     */
    ~LdapSearchDialog() override;

    /**
     * Sets the @p text in the search line edit.
     */
    void setSearchText(const QString &text);

    /**
     * Returns a list of contacts that have been selected
     * in the LDAP search.
     */
    KContacts::Addressee::List selectedContacts() const;

Q_SIGNALS:
    /**
     * This signal is emitted whenever the user clicked the
     * 'Add Selected' button.
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
    //@cond PRIVATE
    class LdapSearchDialogPrivate;
    std::unique_ptr<LdapSearchDialogPrivate> const d;

    Q_PRIVATE_SLOT(d, void slotAddResult(const KLDAP::LdapClient &, const KLDAP::LdapObject &))
    Q_PRIVATE_SLOT(d, void slotStartSearch())
    Q_PRIVATE_SLOT(d, void slotStopSearch())
    Q_PRIVATE_SLOT(d, void slotSearchDone())
    //@endcond
};
}
Q_DECLARE_METATYPE(PimCommon::LdapSearchDialog::FilterType)
