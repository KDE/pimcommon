/*
  SPDX-FileCopyrightText: 2016-2024 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "configureplugindialog.h"
using namespace Qt::Literals::StringLiterals;

#include <KConfigGroup>
#include <KSharedConfig>
#include <KWindowConfig>
#include <PimCommon/PimUtil>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWindow>

using namespace PimCommon;
namespace
{
static const char myConfigurePluginDialogGroupName[] = "ConfigurePluginDialog";
}

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
    mButtonBox->setObjectName("buttonBox"_L1);
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
    // Reimplement it.
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
    create(); // ensure a window is created
    windowHandle()->resize(QSize(600, 400));
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myConfigurePluginDialogGroupName));
    KWindowConfig::restoreWindowSize(windowHandle(), group);
    resize(windowHandle()->size()); // workaround for QTBUG-40584
}

void ConfigurePluginDialog::saveConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), QStringLiteral("ConfigurePluginDialog"));
    group.writeEntry("Size", size());
    group.sync();
}

#include "moc_configureplugindialog.cpp"
