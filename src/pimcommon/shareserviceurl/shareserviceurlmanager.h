/*
  SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

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
/*!
 * \class ShareServiceUrlManager
 * \brief The ShareServiceUrlManager class manages service URLs for sharing
 * \inmodule PimCommon
 * \inheaderfile PimCommon/ShareServiceUrlManager
 * \author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT ShareServiceUrlManager : public QObject
{
    Q_OBJECT
public:
    /*!
     * Constructs a ShareServiceUrlManager.
     * @param parent The parent QObject
     */
    explicit ShareServiceUrlManager(QObject *parent = nullptr);
    /*!
     * Destructs the ShareServiceUrlManager.
     */
    ~ShareServiceUrlManager() override;
    enum ServiceType {
        Fbook = 0,
        Twitter,
        MailTo,
        LinkedIn,
        Evernote,
        LiveJournal,
        ServiceEndType,
    };

    /*!
     * Returns the menu containing the share service actions.
     * @return A KActionMenu with share service options
     */
    [[nodiscard]] KActionMenu *menu() const;

    /*!
     * Generates a service URL for sharing.
     * @param link The link to share
     * @param title The title for the shared link
     * @param type The type of service to use
     * @return A QUrl for the share service
     */
    [[nodiscard]] QUrl generateServiceUrl(const QString &link, const QString &title, ServiceType type);

    /*!
     * Opens a URL in the default browser or service.
     * @param url The URL to open
     */
    void openUrl(const QUrl &url);

public Q_SLOTS:
    /*!
     * Called when a service is selected from the menu.
     * @param act The action that was selected
     */
    void slotSelectServiceUrl(QAction *act);

Q_SIGNALS:
    /*!
     * Emitted when a service URL has been selected.
     * @param type The type of service selected
     */
    void serviceUrlSelected(PimCommon::ShareServiceUrlManager::ServiceType type);

private:
    std::unique_ptr<ShareServiceUrlManagerPrivate> const d;
};
}
Q_DECLARE_METATYPE(PimCommon::ShareServiceUrlManager::ServiceType)
