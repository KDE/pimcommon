/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "checknewversiondialog.h"
#include "checknewversionwidget.h"
#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QVBoxLayout>
using namespace PimCommon;
CheckNewVersionDialog::CheckNewVersionDialog(QWidget *parent)
    : QDialog(parent)
    , mVerifyNewVersionWidget(new CheckNewVersionWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Check New Version"));

    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));

    mVerifyNewVersionWidget->setObjectName(QStringLiteral("mVerifyNewVersionWidget"));
    mainLayout->addWidget(mVerifyNewVersionWidget);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Close, this);
    buttonBox->setObjectName(QStringLiteral("buttonBox"));
    mainLayout->addWidget(buttonBox);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &CheckNewVersionDialog::reject);
}

CheckNewVersionDialog::~CheckNewVersionDialog() = default;

void CheckNewVersionDialog::checkNewVersion()
{
    mVerifyNewVersionWidget->checkNewVersion();
}

void CheckNewVersionDialog::setUrl(const QUrl &url)
{
    mVerifyNewVersionWidget->setUrl(url);
}

#include "moc_checknewversiondialog.cpp"
