/*******************************************************************************
**
** SPDX-FileCopyrightText: 2005 Till Adam <adam@kde.org>
**
** SPDX-License-Identifier: GPL-2.0-or-later
**
*******************************************************************************/
#ifndef PIMCOMMONAKONADI_MAILUTIL_H
#define PIMCOMMONAKONADI_MAILUTIL_H

#include "pimcommonakonadi_export.h"
#include <AkonadiCore/collection.h>

namespace PimCommon
{
/**
 * The Util namespace contains a collection of helper functions use in
 * various places.
 */
namespace MailUtil
{
Q_REQUIRED_RESULT PIMCOMMONAKONADI_EXPORT QString indexerServiceName();
Q_REQUIRED_RESULT PIMCOMMONAKONADI_EXPORT bool isImapFolder(const Akonadi::Collection &col, bool &isOnline);
}
}

#endif
