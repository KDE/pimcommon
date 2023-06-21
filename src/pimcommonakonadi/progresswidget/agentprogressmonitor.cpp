/*
    SPDX-FileCopyrightText: 2009 Constantin Berzan <exit3219@gmail.com>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "agentprogressmonitor.h"

#include <Akonadi/AgentManager>

using namespace Akonadi;
using namespace PimCommon;

AgentProgressMonitor::AgentProgressMonitor(const AgentInstance &agent, KPIM::ProgressItem *item)
    : QObject(item)
    , mAgent(agent)
    , mItem(item)
{
    connect(AgentManager::self(), &AgentManager::instanceProgressChanged, this, &AgentProgressMonitor::instanceProgressChanged);
    connect(AgentManager::self(), &AgentManager::instanceStatusChanged, this, &AgentProgressMonitor::instanceStatusChanged);
    connect(Akonadi::AgentManager::self(), &AgentManager::instanceRemoved, this, &AgentProgressMonitor::instanceRemoved);
    connect(Akonadi::AgentManager::self(), &AgentManager::instanceNameChanged, this, &AgentProgressMonitor::instanceNameChanged);
    // TODO connect to instanceError, instanceWarning, instanceOnline ?
    // and do what?

    connect(item, &KPIM::ProgressItem::progressItemCanceled, this, &AgentProgressMonitor::abort);

    // TODO handle offline case
}

AgentProgressMonitor::~AgentProgressMonitor() = default;

void AgentProgressMonitor::abort()
{
    mAgent.abortCurrentTask();
}

void AgentProgressMonitor::instanceRemoved(const Akonadi::AgentInstance &instance)
{
    Q_UNUSED(instance)

    if (!mItem.data()) {
        return;
    }

    mItem.data()->disconnect(this); // avoid abort call
    mItem.data()->cancel();
    if (mItem.data()) {
        mItem.data()->setComplete();
    }
}

void AgentProgressMonitor::instanceProgressChanged(const AgentInstance &instance)
{
    if (!mItem.data()) {
        return;
    }

    if (mAgent == instance) { // compares identifiers
        mAgent = instance; // keeps copy of current status
        const int progress = mAgent.progress();
        if (progress >= 0) {
            mItem.data()->setProgress(progress);
        }
    }
}

void AgentProgressMonitor::instanceStatusChanged(const AgentInstance &instance)
{
    if (!mItem.data()) {
        return;
    }

    if (mAgent == instance) { // compares identifiers
        mAgent = instance; // keeps copy of current status
        mItem.data()->setStatus(mAgent.statusMessage());
        switch (mAgent.status()) {
        case AgentInstance::Idle:
            if (mItem.data()) {
                mItem.data()->setComplete();
            }
            break;
        case AgentInstance::Running:
            break;
        case AgentInstance::Broken:
            mItem.data()->disconnect(this); // avoid abort call
            mItem.data()->cancel();
            if (mItem.data()) {
                mItem.data()->setComplete();
            }
            break;
        default:
            Q_ASSERT(false);
        }
    }
}

void AgentProgressMonitor::instanceNameChanged(const Akonadi::AgentInstance &instance)
{
    if (!mItem.data()) {
        return;
    }
    mItem.data()->setLabel(instance.name());
}

#include "moc_agentprogressmonitor.cpp"
