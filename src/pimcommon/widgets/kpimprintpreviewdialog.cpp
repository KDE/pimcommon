/*
  SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "kpimprintpreviewdialog.h"
#include <KConfigGroup>
#include <KSharedConfig>

using namespace PimCommon;

KPimPrintPreviewDialog::KPimPrintPreviewDialog(QWidget *parent)
    : QPrintPreviewDialog(parent)
{
    readConfig();
}

KPimPrintPreviewDialog::KPimPrintPreviewDialog(QPrinter *printer, QWidget *parent)
    : QPrintPreviewDialog(printer, parent)
{
    readConfig();
}

KPimPrintPreviewDialog::~KPimPrintPreviewDialog()
{
    writeConfig();
}

void KPimPrintPreviewDialog::readConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), "KPimPrintPreviewDialog");
    const QSize size = group.readEntry("Size", QSize(800, 600));
    if (size.isValid()) {
        resize(size);
    }
}

void KPimPrintPreviewDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), "KPimPrintPreviewDialog");
    group.writeEntry("Size", size());
    group.sync();
}
