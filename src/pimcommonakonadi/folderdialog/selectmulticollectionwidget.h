/*
  Copyright (c) 2013-2020 Laurent Montel <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef SELECTMULTICOLLECTIONWIDGET_H
#define SELECTMULTICOLLECTIONWIDGET_H

#include <QWidget>
#include <Collection>
#include <QModelIndex>

namespace PimCommon {
class CheckedCollectionWidget;
class SelectMultiCollectionWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SelectMultiCollectionWidget(const QString &mimetype, const QList<Akonadi::Collection::Id> &selectedCollection, QWidget *parent = nullptr);
    explicit SelectMultiCollectionWidget(const QString &mimetype, QWidget *parent = nullptr);
    ~SelectMultiCollectionWidget();

    Q_REQUIRED_RESULT QVector<Akonadi::Collection> selectedCollection(const QModelIndex &parent = QModelIndex()) const;

private:
    void slotCollectionsTreeFetched();
    void initialize(const QString &mimetype);
    void updateStatus(const QModelIndex &parent);
    PimCommon::CheckedCollectionWidget *mCheckedCollectionWidget = nullptr;
    QList<Akonadi::Collection::Id> mListCollection;
};
}

#endif // SELECTMULTICOLLECTIONWIDGET_H
