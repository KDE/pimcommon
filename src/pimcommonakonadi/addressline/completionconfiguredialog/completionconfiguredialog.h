/*
  SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#pragma once

#include "pimcommonakonadi_export.h"

#include <QDialog>
class KConfig;
namespace KLDAPCore
{
class LdapClientSearch;
class LdapActivitiesAbstract;
}
namespace PimCommon
{
class CompletionConfigureDialogPrivate;
/*!
 * \class CompletionConfigureDialog
 * \brief The CompletionConfigureDialog class provides configuration for address completion
 * \inmodule PimCommonAkonadi
 * \inheaderfile PimCommonAkonadi/CompletionConfigureDialog
 * \author Laurent Montel <montel@kde.org>
 */
class PIMCOMMONAKONADI_EXPORT CompletionConfigureDialog : public QDialog
{
    Q_OBJECT
public:
    /*!
     * Constructs a CompletionConfigureDialog.
     * @param parent The parent widget
     */
    explicit CompletionConfigureDialog(QWidget *parent = nullptr);
    /*!
     * Destructs the CompletionConfigureDialog.
     */
    ~CompletionConfigureDialog() override;

    /*!
     * Loads the current configuration.
     */
    void load();
    /*!
     * Sets the email blacklist.
     * @param lst The list of blacklisted email addresses
     */
    void setEmailBlackList(const QStringList &lst);
    /*!
     * Sets the LDAP client search object.
     * @param ldapSearch The LdapClientSearch instance
     */
    void setLdapClientSearch(KLDAPCore::LdapClientSearch *ldapSearch);
    /*!
     * Sets the list of recent addresses.
     * @param lst The list of recent addresses
     */
    void setRecentAddresses(const QStringList &lst);
    /*!
     * Checks if the recent address list was changed.
     * @return true if recent addresses were modified, false otherwise
     */
    [[nodiscard]] bool recentAddressWasChanged() const;
    /*!
     * Stores addresses to configuration.
     * @param config The KConfig object to store to
     */
    void storeAddresses(KConfig *config);

    /*!
     * Sets the LDAP activities abstract object.
     * @param ldapActivities The LdapActivitiesAbstract instance
     */
    void setLdapActivitiesAbstract(KLDAPCore::LdapActivitiesAbstract *ldapActivities);

private:
    PIMCOMMONAKONADI_NO_EXPORT void slotSaveAndClose();
    PIMCOMMONAKONADI_NO_EXPORT void slotSave();
    PIMCOMMONAKONADI_NO_EXPORT void readConfig();
    PIMCOMMONAKONADI_NO_EXPORT void slotRestoreToDefaults();
    PIMCOMMONAKONADI_NO_EXPORT void writeConfig();
    std::unique_ptr<CompletionConfigureDialogPrivate> const d;
};
}
