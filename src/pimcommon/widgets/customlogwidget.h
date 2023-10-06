/*
   SPDX-FileCopyrightText: 2012-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once

#include "pimcommon_export.h"
#include <QListWidget>
#include <QStyledItemDelegate>

class QTextDocument;

namespace PimCommon
{
class LogItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit LogItemDelegate(QObject *parent);
    ~LogItemDelegate() override;

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QWidget *createEditor(QWidget *, const QStyleOptionViewItem &, const QModelIndex &) const override;

private:
    QTextDocument *document(const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

class PIMCOMMON_EXPORT CustomLogWidget : public QListWidget
{
public:
    explicit CustomLogWidget(QWidget *parent = nullptr);
    ~CustomLogWidget() override;

    void addInfoLogEntry(const QString &log);
    void addErrorLogEntry(const QString &log);
    void addTitleLogEntry(const QString &log);
    void addEndLineLogEntry();

    [[nodiscard]] QString toHtml() const;
    [[nodiscard]] QString toPlainText() const;
    [[nodiscard]] bool isEmpty() const;

private:
    enum ItemType {
        ItemLogType = Qt::UserRole + 1,
    };

    enum LogType {
        Title = 0,
        Error,
        Info,
        EndLine,
    };
};
}
