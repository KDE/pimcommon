/*
   SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once
#include "pimcommon_export.h"
#include <KMessageWidget>
namespace PimCommon
{
class PIMCOMMON_EXPORT WhatsNewMessageWidget : public KMessageWidget
{
    Q_OBJECT
public:
    explicit WhatsNewMessageWidget(QWidget *parent = nullptr);
    ~WhatsNewMessageWidget() override;

private:
    PIMCOMMON_NO_EXPORT void slotLinkActivated(const QString &contents);
};
}
