/*
  Copyright (c) 2016-2017 Montel Laurent <montel@kde.org>

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
#include <QDialogButtonBox>
#include <QPushButton>
#include <KConfigGroup>
#include <KSharedConfig>
#include <PimCommon/PimUtil>

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

    mButtonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel | QDialogButtonBox::RestoreDefaults | QDialogButtonBox::Help, this);
    mButtonBox->setObjectName(QStringLiteral("buttonBox"));
    layout->addWidget(mButtonBox);
    connect(mButtonBox, &QDialogButtonBox::accepted, this, &ConfigurePluginDialog::slotAccepted);
    connect(mButtonBox, &QDialogButtonBox::rejected, this, &ConfigurePluginDialog::reject);
    connect(mButtonBox, &QDialogButtonBox::helpRequested, this, &ConfigurePluginDialog::slotHelpClicked);
    connect(mButtonBox->button(QDialogButtonBox::RestoreDefaults), &QPushButton::clicked, this, &ConfigurePluginDialog::slotRestoreDefaultClicked);
    readConfig();
    load();
}

void ConfigurePluginDialog::reset()
{
    //Reimplement it.
}

void ConfigurePluginDialog::help()
{
}

QDialogButtonBox *ConfigurePluginDialog::buttonBox() const
{
    return mButtonBox;
}

void ConfigurePluginDialog::showHelp(const QString &name, const QString &anchor)
{
    PimCommon::Util::invokeHelp(name, anchor);
}

void ConfigurePluginDialog::slotHelpClicked()
{
    help();
}

void ConfigurePluginDialog::slotRestoreDefaultClicked()
{
    reset();
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
