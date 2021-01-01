/*
  SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "acllistview.h"
#include <KLocalizedString>
#include <QPainter>

using namespace PimCommon;

AclListView::AclListView(QWidget *parent)
    : QListView(parent)
{
}

AclListView::~AclListView()
{
}

void AclListView::slotCollectionCanBeAdministrated(bool b)
{
    if (mCanBeAdministrated != b) {
        mCanBeAdministrated = b;
        update();
    }
}

void AclListView::generalPaletteChanged()
{
    const QPalette palette = viewport()->palette();
    QColor color = palette.text().color();
    color.setAlpha(128);
    mTextColor = color;
}

void AclListView::paintEvent(QPaintEvent *event)
{
    if (!mCanBeAdministrated) {
        QPainter p(viewport());

        QFont font = p.font();
        font.setItalic(true);
        p.setFont(font);

        if (!mTextColor.isValid()) {
            generalPaletteChanged();
        }
        p.setPen(mTextColor);

        p.drawText(QRect(0, 0, width(), height()), Qt::AlignCenter, i18n("Folder cannot be administrated."));
    } else {
        QListView::paintEvent(event);
    }
}
