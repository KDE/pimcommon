/*
  Copyright (c) 2014-2020 Laurent Montel <montel@kde.org>

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

#include "contenttypewidget.h"
#include "collectiontypeutil.h"
#include <KLocalizedString>
#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>

using namespace PimCommon;

class PimCommon::ContentTypeWidgetPrivate
{
public:
    ContentTypeWidgetPrivate()
        : mContentsComboBox(nullptr)
    {
    }

    QComboBox *mContentsComboBox = nullptr;
};

ContentTypeWidget::ContentTypeWidget(QWidget *parent)
    : QWidget(parent)
    , d(new PimCommon::ContentTypeWidgetPrivate)
{
    QHBoxLayout *hbox = new QHBoxLayout(this);
    hbox->setContentsMargins(0, 0, 0, 0);

    QLabel *label = new QLabel(i18n("&Folder contents:"), this);
    label->setObjectName(QStringLiteral("contenttypewidgetlabel"));
    hbox->addWidget(label);
    d->mContentsComboBox = new QComboBox(this);
    d->mContentsComboBox->setObjectName(QStringLiteral("contentcombobox"));
    label->setBuddy(d->mContentsComboBox);
    hbox->addWidget(d->mContentsComboBox);
    PimCommon::CollectionTypeUtil collectionUtil;
    d->mContentsComboBox->addItem(collectionUtil.folderContentDescription(CollectionTypeUtil::ContentsTypeMail));
    d->mContentsComboBox->addItem(collectionUtil.folderContentDescription(CollectionTypeUtil::ContentsTypeCalendar));
    d->mContentsComboBox->addItem(collectionUtil.folderContentDescription(CollectionTypeUtil::ContentsTypeContact));
    d->mContentsComboBox->addItem(collectionUtil.folderContentDescription(CollectionTypeUtil::ContentsTypeNote));
    d->mContentsComboBox->addItem(collectionUtil.folderContentDescription(CollectionTypeUtil::ContentsTypeTask));
    d->mContentsComboBox->addItem(collectionUtil.folderContentDescription(CollectionTypeUtil::ContentsTypeJournal));
    d->mContentsComboBox->addItem(collectionUtil.folderContentDescription(CollectionTypeUtil::ContentsTypeConfiguration));
    d->mContentsComboBox->addItem(collectionUtil.folderContentDescription(CollectionTypeUtil::ContentsTypeFreebusy));
    d->mContentsComboBox->addItem(collectionUtil.folderContentDescription(CollectionTypeUtil::ContentsTypeFile));

    connect(d->mContentsComboBox, QOverload<int>::of(&QComboBox::activated), this, &ContentTypeWidget::activated);
}

ContentTypeWidget::~ContentTypeWidget()
{
    delete d;
}

int ContentTypeWidget::currentIndex() const
{
    return d->mContentsComboBox->currentIndex();
}

void ContentTypeWidget::setCurrentIndex(int index)
{
    d->mContentsComboBox->setCurrentIndex(index);
}

void ContentTypeWidget::setCurrentItem(const QString &name)
{
    const int pos = d->mContentsComboBox->findText(name);
    if (pos != -1) {
        d->mContentsComboBox->setCurrentIndex(pos);
    }
}

QString ContentTypeWidget::currentText() const
{
    return d->mContentsComboBox->currentText();
}
