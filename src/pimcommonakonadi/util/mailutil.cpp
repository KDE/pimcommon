/*******************************************************************************
**
** SPDX-FileCopyrightText: 2005 Till Adam <adam@kde.org>
**
** SPDX-License-Identifier: GPL-2.0-or-later
**
*******************************************************************************/

#include "mailutil.h"
#include <PimCommon/PimUtil>

#include <AgentInstance>
#include <AkonadiCore/AgentManager>
#include <AkonadiCore/ServerManager>

bool PimCommon::MailUtil::isImapFolder(const Akonadi::Collection &col, bool &isOnline)
{
    const Akonadi::AgentInstance agentInstance = Akonadi::AgentManager::self()->instance(col.resource());
    isOnline = agentInstance.isOnline();

    return PimCommon::Util::isImapResource(agentInstance.type().identifier());
}

QString PimCommon::MailUtil::indexerServiceName()
{
    return Akonadi::ServerManager::agentServiceName(Akonadi::ServerManager::Agent, QStringLiteral("akonadi_indexing_agent"));
}
