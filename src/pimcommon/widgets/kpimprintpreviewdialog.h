/*
  SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef KPIMPRINTPREVIEWDIALOG_H
#define KPIMPRINTPREVIEWDIALOG_H

#include <QPrintPreviewDialog>
#include "pimcommon_export.h"

namespace PimCommon {
/**
 * @brief The KPimPrintPreviewDialog class
 * @author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT KPimPrintPreviewDialog : public QPrintPreviewDialog
{
    Q_OBJECT
public:
    explicit KPimPrintPreviewDialog(QWidget *parent = nullptr);
    explicit KPimPrintPreviewDialog(QPrinter *printer, QWidget *parent = nullptr);
    ~KPimPrintPreviewDialog();
private:
    void readConfig();
    void writeConfig();
};
}

#endif // KPIMPRINTPREVIEWDIALOG_H
