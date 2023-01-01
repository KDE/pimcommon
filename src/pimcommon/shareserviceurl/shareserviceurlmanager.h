/*
  SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "pimcommon_export.h"
#include <QObject>
#include <QUrl>
#include <memory>

class KActionMenu;
class QAction;
namespace PimCommon
{
class ShareServiceUrlManagerPrivate;
/**
 * @brief The ShareServiceUrlManager class
 * @author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT ShareServiceUrlManager : public QObject
{
    Q_OBJECT
public:
    explicit ShareServiceUrlManager(QObject *parent = nullptr);
    ~ShareServiceUrlManager() override;
    enum ServiceType {
        Fbook = 0,
        Twitter,
        MailTo,
        LinkedIn,
        Evernote,
        Pocket,
        LiveJournal,
        ServiceEndType,
    };

    Q_REQUIRED_RESULT KActionMenu *menu() const;

    Q_REQUIRED_RESULT QUrl generateServiceUrl(const QString &link, const QString &title, ServiceType type);

    void openUrl(const QUrl &url);

public Q_SLOTS:
    void slotSelectServiceUrl(QAction *act);

Q_SIGNALS:
    void serviceUrlSelected(PimCommon::ShareServiceUrlManager::ServiceType type);

private:
    std::unique_ptr<ShareServiceUrlManagerPrivate> const d;
};
}
Q_DECLARE_METATYPE(PimCommon::ShareServiceUrlManager::ServiceType)
