/*
  SPDX-FileCopyrightText: 2013-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "selectmulticollectiondialog.h"
#include "selectmulticollectionwidget.h"

#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <KWindowConfig>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWindow>

using namespace PimCommon;

class PimCommon::SelectMultiCollectionDialogPrivate
{
public:
    SelectMultiCollectionDialogPrivate() = default;

    SelectMultiCollectionWidget *mSelectMultiCollection = nullptr;
};

namespace
{
static const char myConfigSelectMultiCollectionDialog[] = "SelectMultiCollectionDialog";
}

SelectMultiCollectionDialog::SelectMultiCollectionDialog(const QString &mimetype, const QList<Akonadi::Collection::Id> &selectedCollection, QWidget *parent)
    : QDialog(parent)
    , d(new PimCommon::SelectMultiCollectionDialogPrivate)
{
    initialize(mimetype, selectedCollection);
}

SelectMultiCollectionDialog::SelectMultiCollectionDialog(const QString &mimetype, QWidget *parent)
    : QDialog(parent)
    , d(new PimCommon::SelectMultiCollectionDialogPrivate)
{
    initialize(mimetype);
}

SelectMultiCollectionDialog::~SelectMultiCollectionDialog()
{
    writeConfig();
}

void SelectMultiCollectionDialog::initialize(const QString &mimetype, const QList<Akonadi::Collection::Id> &selectedCollection)
{
    setWindowTitle(i18nc("@title:window", "Select Multiple Folders"));
    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Close, this);
    auto mainLayout = new QVBoxLayout(this);
    QPushButton *okButton = buttonBox->button(QDialogButtonBox::Ok);
    okButton->setDefault(true);
    okButton->setShortcut(Qt::CTRL | Qt::Key_Return);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &SelectMultiCollectionDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &SelectMultiCollectionDialog::reject);

    d->mSelectMultiCollection = new SelectMultiCollectionWidget(mimetype, selectedCollection, this);
    mainLayout->addWidget(d->mSelectMultiCollection);
    mainLayout->addWidget(buttonBox);
    readConfig();
}

void SelectMultiCollectionDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), myConfigSelectMultiCollectionDialog);
    KWindowConfig::saveWindowSize(windowHandle(), group);
}

void SelectMultiCollectionDialog::readConfig()
{
    create(); // ensure a window is created
    windowHandle()->resize(QSize(800, 600));
    KConfigGroup group(KSharedConfig::openStateConfig(), myConfigSelectMultiCollectionDialog);
    KWindowConfig::restoreWindowSize(windowHandle(), group);
    resize(windowHandle()->size()); // workaround for QTBUG-40584
}

QList<Akonadi::Collection> SelectMultiCollectionDialog::selectedCollection() const
{
    return d->mSelectMultiCollection->selectedCollection();
}
