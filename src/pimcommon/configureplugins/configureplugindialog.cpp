/*
  SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
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

void ConfigurePluginDialog::initLayout(bool addSpacer)
{
    auto layout = new QVBoxLayout(this);
    layout->addWidget(createLayout());
    if (addSpacer) {
        layout->addStretch(1);
    }

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
