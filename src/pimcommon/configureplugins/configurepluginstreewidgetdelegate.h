/*
  SPDX-FileCopyrightText: 2024-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "pimcommon_export.h"
#include <QStyledItemDelegate>
namespace PimCommon
{
class PIMCOMMON_EXPORT ConfigurePluginsTreeWidgetDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit ConfigurePluginsTreeWidgetDelegate(QObject *parent = nullptr);
    ~ConfigurePluginsTreeWidgetDelegate() override;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    [[nodiscard]] QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};
}
