/*
  progressmanager.cpp

  SPDX-FileCopyrightText: 2004 Till Adam <adam@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once
#include "pimcommonakonadi_export.h"
#include <Libkdepim/ProgressManager>

#include <Akonadi/AgentInstance>

namespace PimCommon
{
namespace ProgressManagerAkonadi
{
/*!
 */
PIMCOMMONAKONADI_EXPORT KPIM::ProgressItem *createProgressItem(KPIM::ProgressItem *parent,
                                                               const Akonadi::AgentInstance &agent,
                                                               const QString &id,
                                                               const QString &label,
                                                               const QString &status,
                                                               bool canBeCanceled,
                                                               KPIM::ProgressItem::CryptoStatus cryptoStatus);
}
}
