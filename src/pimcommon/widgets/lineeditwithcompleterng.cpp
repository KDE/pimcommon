/*
  SPDX-FileCopyrightText: 2017-2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "lineeditwithcompleterng.h"
#include <KLocalizedString>
#include <QCompleter>
#include <QContextMenuEvent>
#include <QMenu>
#include <QStringListModel>

using namespace PimCommon;
#define MAX_COMPLETION_ITEMS 20
LineEditWithCompleterNg::LineEditWithCompleterNg(QWidget *parent)
    : QLineEdit(parent)
    , mCompleterListModel(new QStringListModel(this))
{
    auto completer = new QCompleter(this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setModel(mCompleterListModel);
    setCompleter(completer);
}

LineEditWithCompleterNg::~LineEditWithCompleterNg() = default;

void LineEditWithCompleterNg::addCompletionItem(const QString &str)
{
    mListCompetion.removeAll(str);
    mListCompetion.prepend(str);
    while (mListCompetion.size() > MAX_COMPLETION_ITEMS) {
        mListCompetion.removeLast();
    }
    mCompleterListModel->setStringList(mListCompetion);
}

void LineEditWithCompleterNg::contextMenuEvent(QContextMenuEvent *e)
{
    QMenu *popup = QLineEdit::createStandardContextMenu();
    if (popup) {
        popup->addSeparator();
        popup->addAction(QIcon::fromTheme(QStringLiteral("edit-clear-locationbar-rtl")),
                         i18n("Clear History"),
                         this,
                         &LineEditWithCompleterNg::slotClearHistory);
        popup->exec(e->globalPos());
        delete popup;
    }
}

void LineEditWithCompleterNg::slotClearHistory()
{
    mListCompetion.clear();
    mCompleterListModel->setStringList(mListCompetion);
}
