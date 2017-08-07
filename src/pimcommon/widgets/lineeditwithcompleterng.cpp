/*
  Copyright (c) 2017 Montel Laurent <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License, version 2, as
  published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
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
{
    QCompleter *completer = new QCompleter(this);
    mCompleterListModel = new QStringListModel(this);
    completer->setModel(mCompleterListModel);
    setCompleter(completer);
}

LineEditWithCompleterNg::~LineEditWithCompleterNg()
{
}

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
        popup->addAction(QIcon::fromTheme(QStringLiteral("edit-clear-locationbar-rtl")), i18n("Clear History"), this, &LineEditWithCompleterNg::slotClearHistory);
        popup->exec(e->globalPos());
        delete popup;
    }
}

void LineEditWithCompleterNg::slotClearHistory()
{
    mListCompetion.clear();
    mCompleterListModel->setStringList(mListCompetion);
}
