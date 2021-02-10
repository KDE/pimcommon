/*
    SPDX-FileCopyrightText: 2009 Constantin Berzan <exit3219@gmail.com>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef PIMCOMMON_AGENTPROGRESSMONITOR_H
#define PIMCOMMON_AGENTPROGRESSMONITOR_H

#include <Libkdepim/ProgressManager> // ProgressItem

#include <AgentInstance>
namespace PimCommon
{
/**
 * @internal
 *
 * This class automatically updates a ProgressItem based on
 * Akonadi::AgentManager's signals, and places the abort() call if the
 * ProgressItem has been cancelled.
 */
class AgentProgressMonitor : public QObject
{
    Q_OBJECT
public:
    // used by our friend ProgressManager
    AgentProgressMonitor(const Akonadi::AgentInstance &mAgent, KPIM::ProgressItem *mItem);
    ~AgentProgressMonitor() override;

private:
    void abort();
    void instanceProgressChanged(const Akonadi::AgentInstance &);
    void instanceStatusChanged(const Akonadi::AgentInstance &);
    void instanceRemoved(const Akonadi::AgentInstance &);
    void instanceNameChanged(const Akonadi::AgentInstance &);

    Akonadi::AgentInstance mAgent;
    QPointer<KPIM::ProgressItem> const mItem;
};
}

#endif
