/*
  Copyright (C) 2017-2018 Montel Laurent <montel@kde.org>

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

#ifndef LINEEDITWITHCOMPLETERNG_H
#define LINEEDITWITHCOMPLETERNG_H

#include <QLineEdit>
#include "pimcommon_export.h"
class QStringListModel;
namespace PimCommon {
class PIMCOMMON_EXPORT LineEditWithCompleterNg : public QLineEdit
{
    Q_OBJECT
public:
    explicit LineEditWithCompleterNg(QWidget *parent = nullptr);
    ~LineEditWithCompleterNg();

    void addCompletionItem(const QString &str);

protected:
    void contextMenuEvent(QContextMenuEvent *e) override;

public Q_SLOTS:
    void slotClearHistory();

private:
    QStringListModel *mCompleterListModel = nullptr;
    QStringList mListCompetion;
};
}
#endif // LINEEDITWITHCOMPLETER_H
