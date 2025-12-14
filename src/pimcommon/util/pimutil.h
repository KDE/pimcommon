/*******************************************************************************
**
** SPDX-FileCopyrightText: 2005 Till Adam <adam@kde.org>
**
** SPDX-License-Identifier: GPL-2.0-or-later
**
*******************************************************************************/
#pragma once

#include "pimcommon_export.h"
#include <QUrl>
class OrgKdeAkonadiImapSettingsInterface;
class QWidget;

#define IMAP_RESOURCE_IDENTIFIER QStringLiteral("akonadi_imap_resource")
#define KOLAB_RESOURCE_IDENTIFIER QStringLiteral("akonadi_kolab_resource")
#define POP3_RESOURCE_IDENTIFIER QStringLiteral("akonadi_pop3_resource")
#define MBOX_RESOURCE_IDENTIFIER QStringLiteral("akonadi_mbox_resource")
#define GMAIL_RESOURCE_IDENTIFIER QStringLiteral("akonadi_gmail_resource")
namespace PimCommon
{
/**
 * The Util namespace contains a collection of helper functions use in
 * various places.
 */
namespace Util
{
[[nodiscard]] PIMCOMMON_EXPORT OrgKdeAkonadiImapSettingsInterface *createImapSettingsInterface(const QString &ident);
PIMCOMMON_EXPORT void saveTextAs(const QString &text, const QString &filter, QWidget *parent, const QUrl &url = QUrl(), const QString &caption = QString());
[[nodiscard]] PIMCOMMON_EXPORT bool saveToFile(const QString &filename, const QString &text);
[[nodiscard]] PIMCOMMON_EXPORT QString loadToFile(const QString &filter, QWidget *parent, const QUrl &url = QUrl(), const QString &caption = QString());
PIMCOMMON_EXPORT void invokeHelp(const QString &docfile, const QString &anchor = QString());
[[nodiscard]] PIMCOMMON_EXPORT bool isImapResource(const QString &identifier);
[[nodiscard]] PIMCOMMON_EXPORT QStringList generateEmailList(const QStringList &list);
// Only for testing
[[nodiscard]] PIMCOMMON_EXPORT QUrl generateHelpUrl(const QString &docfile, const QString &anchor = QString());
}
}
