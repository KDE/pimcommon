/*
   SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "translatorconfiguredialog.h"
#include "translatorconfigurewidget.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <KWindowConfig>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QWindow>
namespace
{
const char myTranslatorConfigureDialogConfigGroupName[] = "TranslatorConfigureDialog";
}

using namespace PimCommonTextTranslator;
TranslatorConfigureDialog::TranslatorConfigureDialog(QWidget *parent)
    : QDialog(parent)
    , mTranslatorConfigureWidget(new TranslatorConfigureWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Configure Translator"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));

    mTranslatorConfigureWidget->setObjectName(QStringLiteral("mTranslatorConfigureWidget"));
    mainLayout->addWidget(mTranslatorConfigureWidget);
    mainLayout->addStretch();

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    buttonBox->setObjectName(QStringLiteral("buttonBox"));
    mainLayout->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &TranslatorConfigureDialog::slotAccept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &TranslatorConfigureDialog::reject);
    mTranslatorConfigureWidget->loadSettings();
    readConfig();
}

TranslatorConfigureDialog::~TranslatorConfigureDialog()
{
    writeConfig();
}

void TranslatorConfigureDialog::slotAccept()
{
    mTranslatorConfigureWidget->saveSettings();
    accept();
}

void TranslatorConfigureDialog::readConfig()
{
    create(); // ensure a window is created
    windowHandle()->resize(QSize(600, 400));
    KConfigGroup group(KSharedConfig::openStateConfig(), myTranslatorConfigureDialogConfigGroupName);
    KWindowConfig::restoreWindowSize(windowHandle(), group);
    resize(windowHandle()->size()); // workaround for QTBUG-40584
}

void TranslatorConfigureDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), myTranslatorConfigureDialogConfigGroupName);
    KWindowConfig::saveWindowSize(windowHandle(), group);
    group.sync();
}
