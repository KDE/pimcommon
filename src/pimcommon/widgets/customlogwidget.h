/*
   SPDX-FileCopyrightText: 2012-2026 Laurent Montel <montel@kde.org>

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
    /*!
     * Constructs a LogItemDelegate.
     * @param parent The parent QObject
     */
    explicit LogItemDelegate(QObject *parent);
    /*!
     * Destructs the LogItemDelegate.
     */
    ~LogItemDelegate() override;

    /*!
     * Returns the size hint for the item.
     * @param option The style option
     * @param index The model index
     * @return The size hint
     */
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    /*!
     * Paints the item.
     * @param painter The painter to use
     * @param option The style option
     * @param index The model index
     */
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    /*!
     * Creates an editor for the item (disabled).
     * @return nullptr
     */
    [[nodiscard]] QWidget *createEditor(QWidget *, const QStyleOptionViewItem &, const QModelIndex &) const override;

private:
    QTextDocument *document(const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

/*!
 * \class CustomLogWidget
 * \brief The CustomLogWidget class provides a widget for displaying custom log messages
 * \inmodule PimCommon
 * \inheaderfile PimCommon/CustomLogWidget
 */
class PIMCOMMON_EXPORT CustomLogWidget : public QListWidget
{
public:
    /*!
     * Constructs a CustomLogWidget.
     * @param parent The parent widget
     */
    explicit CustomLogWidget(QWidget *parent = nullptr);
    /*!
     * Destructs the CustomLogWidget.
     */
    ~CustomLogWidget() override;

    /*!
     * Adds an info log entry to the widget.
     * @param log The log message to add
     */
    void addInfoLogEntry(const QString &log);
    /*!
     * Adds an error log entry to the widget.
     * @param log The error message to add
     */
    void addErrorLogEntry(const QString &log);
    /*!
     * Adds a title log entry to the widget.
     * @param log The title to add
     */
    void addTitleLogEntry(const QString &log);
    /*!
     * Adds an end-of-line log entry.
     */
    void addEndLineLogEntry();

    /*!
     * Returns the log contents as HTML.
     * @return The log as HTML string
     */
    [[nodiscard]] QString toHtml() const;
    /*!
     * Returns the log contents as plain text.
     * @return The log as plain text string
     */
    [[nodiscard]] QString toPlainText() const;
    /*!
     * Returns whether the log is empty.
     * @return true if the log has no entries, false otherwise
     */
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
