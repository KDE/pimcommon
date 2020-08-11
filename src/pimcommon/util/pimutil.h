/*******************************************************************************
**
** SPDX-FileCopyrightText: 2005 Till Adam <adam@kde.org>
**
** SPDX-License-Identifier: GPL-2.0-or-later
**
*******************************************************************************/
#ifndef PIMCOMMON_PIMUTIL_H
#define PIMCOMMON_PIMUTIL_H

#include "pimcommon_export.h"
#include <QUrl>
class OrgKdeAkonadiImapSettingsInterface;
class QWidget;

#define IMAP_RESOURCE_IDENTIFIER QStringLiteral("akonadi_imap_resource")
#define KOLAB_RESOURCE_IDENTIFIER QStringLiteral("akonadi_kolab_resource")
#define POP3_RESOURCE_IDENTIFIER QStringLiteral("akonadi_pop3_resource")
#define MBOX_RESOURCE_IDENTIFIER QStringLiteral("akonadi_mbox_resource")
#define GMAIL_RESOURCE_IDENTIFIER QStringLiteral("akonadi_gmail_resource")
namespace PimCommon {
/**
 * The Util namespace contains a collection of helper functions use in
 * various places.
 */
namespace Util {
Q_REQUIRED_RESULT PIMCOMMON_EXPORT OrgKdeAkonadiImapSettingsInterface *createImapSettingsInterface(const QString &ident);
PIMCOMMON_EXPORT void saveTextAs(const QString &text, const QString &filter, QWidget *parent, const QUrl &url = QUrl(), const QString &caption = QString());
Q_REQUIRED_RESULT PIMCOMMON_EXPORT bool saveToFile(const QString &filename, const QString &text);
Q_REQUIRED_RESULT PIMCOMMON_EXPORT QString loadToFile(const QString &filter, QWidget *parent, const QUrl &url = QUrl(), const QString &caption = QString());
PIMCOMMON_EXPORT void invokeHelp(const QString &docfile, const QString &anchor = QString());
Q_REQUIRED_RESULT PIMCOMMON_EXPORT bool isImapResource(const QString &identifier);
Q_REQUIRED_RESULT PIMCOMMON_EXPORT QStringList generateEmailList(const QStringList &list);
}
}

#endif
