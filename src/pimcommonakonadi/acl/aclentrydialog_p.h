/*
 * SPDX-FileCopyrightText: 2010 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
 * SPDX-FileCopyrightText: 2010 Tobias Koenig <tokoe@kdab.com>
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

#include <KIMAP/Acl>

#include <QDialog>

namespace PimCommon
{
/**
 * @short A dialog for editing an IMAP ACL entry.
 */
class AclEntryDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * Creates a new ACL entry dialog.
     *
     * @param parent The parent widget.
     */
    explicit AclEntryDialog(QWidget *parent = nullptr);

    /**
     * Destroys the ACL entry dialog.
     */
    ~AclEntryDialog() override;

    /**
     * Sets the user @p id of the ACL entry.
     */
    void setUserId(const QString &id);

    /**
     * Returns the user id of the ACL entry.
     */
    [[nodiscard]] QString userId() const;

    /**
     * Sets the permissions of the ACL entry.
     */
    void setPermissions(KIMAP::Acl::Rights permissions);

    /**
     * Returns the permissions of the ACL entry.
     */
    [[nodiscard]] KIMAP::Acl::Rights permissions() const;

private:
    class AclEntryDialogPrivate;
    std::unique_ptr<AclEntryDialogPrivate> const d;
};
}
