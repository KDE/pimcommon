/*
  SPDX-FileCopyrightText: 2014-2024 Laurent Montel <montel@kde.org>
  SPDX-FileCopyrightText: 2021 Carl Schwan <carlschwan@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "contenttypewidget.h"
#include "collectiontypeutil.h"
#include <KLocalizedString>

using namespace PimCommon;

ContentTypeWidget::ContentTypeWidget(QWidget *parent)
    : QComboBox(parent)
{
    setObjectName(QLatin1StringView("contentcombobox"));
    PimCommon::CollectionTypeUtil collectionUtil;
    addItem(collectionUtil.folderContentDescription(CollectionTypeUtil::ContentsTypeMail));
    addItem(collectionUtil.folderContentDescription(CollectionTypeUtil::ContentsTypeCalendar));
    addItem(collectionUtil.folderContentDescription(CollectionTypeUtil::ContentsTypeContact));
    addItem(collectionUtil.folderContentDescription(CollectionTypeUtil::ContentsTypeNote));
    addItem(collectionUtil.folderContentDescription(CollectionTypeUtil::ContentsTypeTask));
    addItem(collectionUtil.folderContentDescription(CollectionTypeUtil::ContentsTypeJournal));
    addItem(collectionUtil.folderContentDescription(CollectionTypeUtil::ContentsTypeConfiguration));
    addItem(collectionUtil.folderContentDescription(CollectionTypeUtil::ContentsTypeFreebusy));
    addItem(collectionUtil.folderContentDescription(CollectionTypeUtil::ContentsTypeFile));
}

ContentTypeWidget::~ContentTypeWidget() = default;

void ContentTypeWidget::setCurrentItem(const QString &name)
{
    const int pos = findText(name);
    if (pos != -1) {
        QComboBox::setCurrentIndex(pos);
    }
}

QString ContentTypeWidget::labelName()
{
    return i18n("&Folder contents:");
}

#include "moc_contenttypewidget.cpp"
