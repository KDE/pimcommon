/*
  Copyright (c) 2015-2019 Montel Laurent <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef IMAPRESOURCECAPABILITIESMANAGER_H
#define IMAPRESOURCECAPABILITIESMANAGER_H

#include <QObject>
#include <QHash>

#include "pimcommonakonadi_export.h"
class QDBusPendingCallWatcher;
namespace Akonadi {
class AgentInstance;
}
namespace PimCommon {
/**
 * @brief The ImapResourceCapabilitiesManager class
 * @author Laurent Montel <montel@kde.org>
 */
class PIMCOMMONAKONADI_EXPORT ImapResourceCapabilitiesManager : public QObject
{
    Q_OBJECT
public:
    explicit ImapResourceCapabilitiesManager(QObject *parent = nullptr);
    ~ImapResourceCapabilitiesManager();

    Q_REQUIRED_RESULT bool hasAnnotationSupport(const QString &identifier) const;

private:
    void slotInstanceAdded(const Akonadi::AgentInstance &instance);
    void slotInstanceRemoved(const Akonadi::AgentInstance &instance);
    void slotCapabilities(QDBusPendingCallWatcher *watcher);

    void init();
    void searchCapabilities(const QString &identifier);
    QHash<QString, bool> mImapResource;
};
}

#endif // IMAPRESOURCECAPABILITIESMANAGER_H
