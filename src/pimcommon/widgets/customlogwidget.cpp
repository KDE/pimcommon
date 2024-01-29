/*
   SPDX-FileCopyrightText: 2012-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "customlogwidget.h"
#include <KColorScheme>
#include <QAbstractTextDocumentLayout>
#include <QApplication>
#include <QPainter>
#include <QTextDocument>

using namespace PimCommon;

LogItemDelegate::LogItemDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

LogItemDelegate::~LogItemDelegate() = default;

QTextDocument *LogItemDelegate::document(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (!index.isValid()) {
        return nullptr;
    }
    auto document = new QTextDocument(nullptr);
    document->setDocumentMargin(1);
    const auto textColor = index.data(Qt::ForegroundRole).value<QColor>();
    QStyleOptionViewItem option4 = option;
    QStyledItemDelegate::initStyleOption(&option4, index);

    QString text = option4.text;

    const QString content = QStringLiteral(
                                "<html style=\"color:%1\">"
                                "<body> %2")
                                .arg(textColor.name().toUpper(), text)
        + QLatin1StringView("</table></body></html>");

    document->setHtml(content);

    return document;
}

void LogItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (!index.isValid()) {
        return;
    }
    QTextDocument *doc = document(option, index);
    if (!doc) {
        return;
    }
    doc->setTextWidth(option.rect.width());
    painter->setRenderHint(QPainter::Antialiasing);

    QPen pen = painter->pen();

    QStyleOptionViewItem opt(option);
    opt.showDecorationSelected = true;
    QApplication::style()->drawPrimitive(QStyle::PE_PanelItemViewItem, &opt, painter);
    painter->save();
    painter->translate(option.rect.topLeft());

    doc->drawContents(painter);

    painter->restore();
    painter->setPen(pen);

    delete doc;
}

QSize LogItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (!index.isValid()) {
        return {0, 0};
    }

    QTextDocument *doc = document(option, index);
    if (!doc) {
        return {0, 0};
    }

    const QSize size = doc->documentLayout()->documentSize().toSize();
    delete doc;

    return size;
}

QWidget *LogItemDelegate::createEditor(QWidget *, const QStyleOptionViewItem &, const QModelIndex &) const
{
    return nullptr;
}

CustomLogWidget::CustomLogWidget(QWidget *parent)
    : QListWidget(parent)
{
    auto itemDelegate = new LogItemDelegate(this);
    setItemDelegate(itemDelegate);
}

CustomLogWidget::~CustomLogWidget() = default;

void CustomLogWidget::addTitleLogEntry(const QString &log)
{
    auto item = new QListWidgetItem(log);
    item->setForeground(palette().color(QPalette::WindowText));
    QFont font = item->font();
    font.setBold(true);
    item->setFont(font);
    item->setData(ItemLogType, Title);
    addItem(item);
    scrollToItem(item);
}

void CustomLogWidget::addInfoLogEntry(const QString &log)
{
    auto item = new QListWidgetItem(log);
    item->setForeground(palette().color(QPalette::WindowText));
    item->setData(ItemLogType, Info);
    addItem(item);
    scrollToItem(item);
}

void CustomLogWidget::addErrorLogEntry(const QString &log)
{
    auto item = new QListWidgetItem(log);
    item->setForeground(KColorScheme().foreground(KColorScheme::NegativeText));
    item->setData(ItemLogType, Error);
    addItem(item);
    scrollToItem(item);
}

void CustomLogWidget::addEndLineLogEntry()
{
    auto item = new QListWidgetItem;
    item->setData(ItemLogType, EndLine);
    addItem(item);
    scrollToItem(item);
}

QString CustomLogWidget::toHtml() const
{
    QString result = QStringLiteral("<html>\n<body>\n");
    result += QLatin1StringView("<meta http-equiv=\"content-type\" content=\"text/html; charset=UTF-8\">\n");
    for (int i = 0; i < count(); ++i) {
        QListWidgetItem *itemWidget = item(i);
        const QString itemText(itemWidget->text());
        QString logText;
        LogType type = static_cast<LogType>(itemWidget->data(CustomLogWidget::ItemLogType).toInt());
        switch (type) {
        case Title:
            logText = QStringLiteral("<font color=%1>%2</font>").arg(QColor(Qt::black).name(), itemText);
            break;
        case Error:
            logText = QStringLiteral("<font color=%1>%2</font>").arg(QColor(Qt::red).name(), itemText);
            break;
        case Info:
            logText = QStringLiteral("<font color=%1>%2</font>").arg(QColor(Qt::darkGreen).name(), itemText);
            break;
        case EndLine:
            logText = QStringLiteral("<br/>");
            break;
        }
        result += QLatin1StringView("<p>") + logText + QLatin1String("</p>") + QLatin1Char('\n');
    }
    result += QLatin1StringView("</body>\n</html>\n");
    return result;
}

QString CustomLogWidget::toPlainText() const
{
    QString result;
    for (int i = 0; i < count(); ++i) {
        result += item(i)->text() + QLatin1Char('\n');
    }
    return result;
}

bool CustomLogWidget::isEmpty() const
{
    return count() == 0;
}

#include "moc_customlogwidget.cpp"
