/*
  SPDX-FileCopyrightText: 2024 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "configurepluginstreewidgetdelegate.h"

#include <QApplication>
#include <QPainter>

using namespace PimCommon;
ConfigurePluginsTreeWidgetDelegate::ConfigurePluginsTreeWidgetDelegate(QObject *parent)
    : QStyledItemDelegate{parent}
{
}

ConfigurePluginsTreeWidgetDelegate::~ConfigurePluginsTreeWidgetDelegate() = default;

void ConfigurePluginsTreeWidgetDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (!index.isValid())
        return;
    QStyleOptionViewItem opt(option);
    opt.showDecorationSelected = true;
    QApplication::style()->drawPrimitive(QStyle::PE_PanelItemViewItem, &opt, painter);

    // Get the text and split it into two lines
    const QString text = index.data(Qt::DisplayRole).toString();
    if (text.isEmpty()) {
        return;
    }
    painter->save();
    const QStringList lines = text.split(QLatin1Char('\n'));

    // Set the painter font
    painter->setFont(option.font);

    // Calculate the text rectangles
    QFontMetrics fontMetrics(option.font);
    const QRect rect = option.rect;

    // Draw the two lines
    painter->setPen(option.palette.text().color());
    const QRect line1Rect(rect.left() + 5, rect.top(), rect.width(), fontMetrics.height());
    painter->drawText(line1Rect, Qt::AlignLeft | Qt::AlignVCenter, lines.at(0));
    if (lines.count() == 2) {
        QFont f = option.font;
        f.setItalic(true);
        f.setPointSize(f.pointSize() - 2);
        painter->setFont(f);
        const QRect line2Rect(rect.left() + 5, rect.top() + fontMetrics.height(), rect.width(), fontMetrics.height());
        painter->drawText(line2Rect, Qt::AlignLeft | Qt::AlignVCenter, lines.at(1));
    }
    painter->restore();
}

QSize ConfigurePluginsTreeWidgetDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QFontMetrics fontMetrics(option.font);
    const int height = fontMetrics.height() * 2; // Height for two lines
    const int width = fontMetrics.horizontalAdvance(index.data(Qt::DisplayRole).toString());
    return QSize(width, height);
}
