/*
  SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "pimcommon_export.h"
#include <KMessageWidget>

namespace PimCommon
{
/*!
 * \class PurposeMenuMessageWidget
 * \brief The PurposeMenuMessageWidget class provides a message widget for displaying Purpose framework results
 * \inmodule PimCommon
 * \inheaderfile PimCommon/PurposeMenuMessageWidget
 * \author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT PurposeMenuMessageWidget : public KMessageWidget
{
    Q_OBJECT
public:
    /*!
     * Constructs a PurposeMenuMessageWidget.
     * @param parent The parent widget
     */
    explicit PurposeMenuMessageWidget(QWidget *parent = nullptr);
    /*!
     * Destructs the PurposeMenuMessageWidget.
     */
    ~PurposeMenuMessageWidget() override;

public Q_SLOTS:
    /*!
     * Called when a share operation fails.
     * @param message The error message
     */
    void slotShareError(const QString &message);
    /*!
     * Called when a share operation succeeds.
     * @param url The shared URL
     */
    void slotShareSuccess(const QString &url);
};
}
