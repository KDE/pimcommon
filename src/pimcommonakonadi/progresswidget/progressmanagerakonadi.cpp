/*
  progressmanager.cpp

  SPDX-FileCopyrightText: 2004 Till Adam <adam@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "progressmanagerakonadi.h"
#include "agentprogressmonitor.h"

KPIM::ProgressItem *PimCommon::ProgressManagerAkonadi::createProgressItem(KPIM::ProgressItem *parent,
                                                                          const Akonadi::AgentInstance &agent,
                                                                          const QString &id,
                                                                          const QString &label,
                                                                          const QString &status,
                                                                          bool canBeCanceled,
                                                                          KPIM::ProgressItem::CryptoStatus cryptoStatus)
{
    const bool itemAlreadyExists = (KPIM::ProgressManager::instance()->progressItem(id) != nullptr);
    KPIM::ProgressItem *t = KPIM::ProgressManager::instance()->createProgressItem(parent, id, label, status, canBeCanceled, cryptoStatus);
    t->setTypeProgressItem(0);
    if (!itemAlreadyExists) {
        //    qCDebug(LIBKDEPIM_LOG) << "Created ProgressItem for agent" << instance.name();
        new AgentProgressMonitor(agent, t);
    }
    return t;
}
