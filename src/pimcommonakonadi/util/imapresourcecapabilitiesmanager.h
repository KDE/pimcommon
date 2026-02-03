/*
  SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QHash>
#include <QObject>

#include "pimcommonakonadi_export.h"
class QDBusPendingCallWatcher;
namespace Akonadi
{
class AgentInstance;
}
namespace PimCommon
{
/*!
 * \class ImapResourceCapabilitiesManager
 * \brief The ImapResourceCapabilitiesManager class manages IMAP resource capabilities
 * \inmodule PimCommonAkonadi
 * \inheaderfile PimCommonAkonadi/ImapResourceCapabilitiesManager
 * \author Laurent Montel <montel@kde.org>
 */
class PIMCOMMONAKONADI_EXPORT ImapResourceCapabilitiesManager : public QObject
{
    Q_OBJECT
public:
    /*!
     * Constructs an ImapResourceCapabilitiesManager.
     * @param parent The parent QObject
     */
    explicit ImapResourceCapabilitiesManager(QObject *parent = nullptr);
    /*!
     * Destructs the ImapResourceCapabilitiesManager.
     */
    ~ImapResourceCapabilitiesManager() override;

    /*!
     * Checks if an IMAP resource supports annotations.
     * @param identifier The identifier of the IMAP resource
     * @return true if annotation support is available, false otherwise
     */
    [[nodiscard]] bool hasAnnotationSupport(const QString &identifier) const;

private:
    PIMCOMMONAKONADI_NO_EXPORT void slotInstanceAdded(const Akonadi::AgentInstance &instance);
    PIMCOMMONAKONADI_NO_EXPORT void slotInstanceRemoved(const Akonadi::AgentInstance &instance);
    PIMCOMMONAKONADI_NO_EXPORT void slotCapabilities(QDBusPendingCallWatcher *watcher);

    PIMCOMMONAKONADI_NO_EXPORT void init();
    PIMCOMMONAKONADI_NO_EXPORT void searchCapabilities(const QString &identifier);
    QHash<QString, bool> mImapResource;
};
}
