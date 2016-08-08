/*
  Copyright (c) 2014-2016 Montel Laurent <montel@kde.org>

  This library is free software; you can redistribute it and/or modify it
  under the terms of the GNU Library General Public License as published by
  the Free Software Foundation; either version 2 of the License, or (at your
  option) any later version.

  This library is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
  License for more details.

  You should have received a copy of the GNU Library General Public License
  along with this library; see the file COPYING.LIB.  If not, write to the
  Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
  02110-1301, USA.

*/

#include "storageservicepropertiesdialog.h"

#include <KLocalizedString>
#include <KSharedConfig>
#include <QLabel>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFormLayout>

using namespace PimCommon;

StorageServicePropertiesDialog::StorageServicePropertiesDialog(const QMap<QString, QString> &information, QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(i18nc("@title:window", "Properties"));

    createInformationWidget(information);
}

StorageServicePropertiesDialog::~StorageServicePropertiesDialog()
{
}

void StorageServicePropertiesDialog::createInformationWidget(const QMap<QString, QString> &information)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QFormLayout *layout = new QFormLayout;
    mainLayout->addLayout(layout);

    QMapIterator<QString, QString> i(information);
    while (i.hasNext()) {
        i.next();
        QLabel *type = new QLabel(this);
        QFont font = type->font();
        font.setBold(true);
        type->setFont(font);
        type->setAlignment(Qt::AlignRight);
        type->setText(i.key());

        QLabel *info = new QLabel(this);
        info->setTextInteractionFlags(Qt::TextBrowserInteraction);
        info->setAlignment(Qt::AlignLeft);
        info->setText(i.value());
        layout->addRow(type, info);
    }
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Close, this);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &StorageServicePropertiesDialog::reject);
    mainLayout->addWidget(buttonBox);
}
