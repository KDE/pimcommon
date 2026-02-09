/*
  SPDX-FileCopyrightText: 2018-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "pimcommon_export.h"
#include <QObject>
namespace Purpose
{
class Menu;
}
class QMenu;
class QTemporaryFile;
namespace PimCommon
{
/*!
 * \class PimCommon::PurposeMenuWidget
 * \brief The PurposeMenuWidget class provides a menu widget for sharing content using Purpose framework
 * \inmodule PimCommon
 * \inheaderfile PimCommon/PurposeMenuWidget
 * \author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT PurposeMenuWidget : public QObject
{
    Q_OBJECT
public:
    /*!
     * Constructs a PurposeMenuWidget.
     * @param parentWidget The parent widget
     * @param parent The parent QObject
     */
    explicit PurposeMenuWidget(QWidget *parentWidget, QObject *parent = nullptr);
    /*!
     * Destructs the PurposeMenuWidget.
     */
    ~PurposeMenuWidget() override;

    /*!
     * Returns the text to be shared.
     * @return The content as a byte array
     */
    [[nodiscard]] virtual QByteArray text() = 0;
    /*!
     * Returns the menu for sharing options.
     * @return A QMenu with share options
     */
    [[nodiscard]] QMenu *menu() const;

Q_SIGNALS:
    /*!
     * Emitted when a sharing error occurs.
     * @param message The error message
     */
    void shareError(const QString &message);
    /*!
     * Emitted when sharing is successful.
     * @param url The shared URL
     */
    void shareSuccess(const QString &url);

private:
    PIMCOMMON_NO_EXPORT void slotInitializeShareMenu();
    PIMCOMMON_NO_EXPORT void slotShareActionFinished(const QJsonObject &output, int error, const QString &message);
    QWidget *const mParentWidget;
    Purpose::Menu *const mShareMenu;
    QTemporaryFile *mTemporaryShareFile = nullptr;
};
}
