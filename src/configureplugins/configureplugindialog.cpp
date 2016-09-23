/*
  Copyright (c) 2016 Montel Laurent <montel@kde.org>

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


#include "configureplugindialog.h"
#include <QVBoxLayout>
#include <KLocalizedString>
#include <QDialogButtonBox>
#include <KConfigGroup>
#include <KSharedConfig>

using namespace PimCommon;

ConfigurePluginDialog::ConfigurePluginDialog(QWidget *parent)
    : QDialog(parent)
{
}

ConfigurePluginDialog::~ConfigurePluginDialog()
{
    saveConfig();
}

void ConfigurePluginDialog::initLayout()
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(createLayout());

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok|QDialogButtonBox::Cancel, this);
    layout->addWidget(buttonBox);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &ConfigurePluginDialog::slotAccepted);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &ConfigurePluginDialog::rejected);
    readConfig();
    load();
}

void ConfigurePluginDialog::slotAccepted()
{
    save();
    accept();
}

void ConfigurePluginDialog::readConfig()
{
    KConfigGroup group(KSharedConfig::openConfig(), "ConfigurePluginDialog");
    const QSize size = group.readEntry("Size", QSize(600, 400));
    if (size.isValid()) {
        resize(size);
    }
}

void ConfigurePluginDialog::saveConfig()
{
    KConfigGroup group(KSharedConfig::openConfig(), "ConfigurePluginDialog");
    group.writeEntry("Size", size());
    group.sync();
}
