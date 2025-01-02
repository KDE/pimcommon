/*
  SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "pimcommon_export.h"
#include <KMessageWidget>

namespace PimCommon
{
/**
 * @brief The PurposeMenuMessageWidget class
 * @author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT PurposeMenuMessageWidget : public KMessageWidget
{
    Q_OBJECT
public:
    explicit PurposeMenuMessageWidget(QWidget *parent = nullptr);
    ~PurposeMenuMessageWidget() override;

public Q_SLOTS:
    void slotShareError(const QString &message);
    void slotShareSuccess(const QString &url);
};
}
