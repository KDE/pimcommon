/*
  SPDX-FileCopyrightText: 2013-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "customtreeview.h"

#include <QPainter>
#include <QFontDatabase>
#include <QEvent>

using namespace PimCommon;

CustomTreeView::CustomTreeView(QWidget *parent)
    : QTreeWidget(parent)
{
}

CustomTreeView::~CustomTreeView()
{
}

void CustomTreeView::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::PaletteChange) {
        generalPaletteChanged();
    } else if (event->type() == QEvent::FontChange) {
        generalFontChanged();
    }
    QTreeWidget::changeEvent(event);
}

void CustomTreeView::setShowDefaultText(bool b)
{
    if (mShowDefaultText != b) {
        mShowDefaultText = b;
        update();
    }
}

bool CustomTreeView::showDefaultText() const
{
    return mShowDefaultText;
}

void CustomTreeView::setDefaultText(const QString &text)
{
    if (mDefaultText != text) {
        mDefaultText = text;
        update();
    }
}

void CustomTreeView::generalPaletteChanged()
{
    const QPalette palette = viewport()->palette();
    QColor color = palette.text().color();
    color.setAlpha(128);
    mTextColor = color;
}

void CustomTreeView::generalFontChanged()
{
    setFont(QFontDatabase::systemFont(QFontDatabase::GeneralFont));
}

void CustomTreeView::paintEvent(QPaintEvent *event)
{
    if (mShowDefaultText && !mDefaultText.isEmpty()) {
        QPainter p(viewport());

        QFont font = p.font();
        font.setItalic(true);
        p.setFont(font);

        if (!mTextColor.isValid()) {
            generalPaletteChanged();
        }
        p.setPen(mTextColor);

        p.drawText(QRect(0, 0, width(), height()), Qt::AlignCenter, mDefaultText);
    } else {
        QTreeWidget::paintEvent(event);
    }
}
