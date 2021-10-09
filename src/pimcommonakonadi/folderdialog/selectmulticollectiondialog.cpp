/*
  SPDX-FileCopyrightText: 2013-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "selectmulticollectiondialog.h"
#include "selectmulticollectionwidget.h"

#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>

using namespace PimCommon;

class PimCommon::SelectMultiCollectionDialogPrivate
{
public:
    SelectMultiCollectionDialogPrivate()
    {
    }

    SelectMultiCollectionWidget *mSelectMultiCollection = nullptr;
};

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

void SelectMultiCollectionDialog::readConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), "SelectMultiCollectionDialog");
    const QSize sizeDialog = group.readEntry("Size", QSize(800, 600));
    if (sizeDialog.isValid()) {
        resize(sizeDialog);
    }
}

void SelectMultiCollectionDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), "SelectMultiCollectionDialog");
    group.writeEntry("Size", size());
}

QVector<Akonadi::Collection> SelectMultiCollectionDialog::selectedCollection() const
{
    return d->mSelectMultiCollection->selectedCollection();
}
