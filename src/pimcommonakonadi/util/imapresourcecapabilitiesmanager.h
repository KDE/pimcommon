/*
  SPDX-FileCopyrightText: 2015-2022 Laurent Montel <montel@kde.org>

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
/**
 * @brief The ImapResourceCapabilitiesManager class
 * @author Laurent Montel <montel@kde.org>
 */
class PIMCOMMONAKONADI_EXPORT ImapResourceCapabilitiesManager : public QObject
{
    Q_OBJECT
public:
    explicit ImapResourceCapabilitiesManager(QObject *parent = nullptr);
    ~ImapResourceCapabilitiesManager() override;

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
