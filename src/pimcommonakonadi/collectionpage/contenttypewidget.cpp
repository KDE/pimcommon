/*
  SPDX-FileCopyrightText: 2014-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

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
