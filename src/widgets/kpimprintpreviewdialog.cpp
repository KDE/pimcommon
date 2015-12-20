/*
  Copyright (c) 2015 Montel Laurent <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License, version 2, as
  published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
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

KPimPrintPreviewDialog::~KPimPrintPreviewDialog()
{
    writeConfig();
}

void KPimPrintPreviewDialog::readConfig()
{
    KConfigGroup group(KSharedConfig::openConfig(), "KPimPrintPreviewDialog");
    const QSize size = group.readEntry("Size", QSize(800, 600));
    if (size.isValid()) {
        resize(size);
    }
}

void KPimPrintPreviewDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openConfig(), "KPimPrintPreviewDialog");
    group.writeEntry("Size", size());
    group.sync();
}
