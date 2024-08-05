/*
   SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once

#include "pimcommon_export.h"
#include <QDialog>
namespace PimCommon
{
class WhatsNewWidget;
class PIMCOMMON_EXPORT WhatsNewDialog : public QDialog
{
    Q_OBJECT
public:
    explicit WhatsNewDialog(QWidget *parent = nullptr);
    ~WhatsNewDialog() override;

    void updateInformations();

private:
    PIMCOMMON_NO_EXPORT void readConfig();
    PIMCOMMON_NO_EXPORT void writeConfig();
    WhatsNewWidget *const mWhatsNewWidget;
};
}
