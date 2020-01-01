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

#ifndef CHECKEDCOLLECTIONWIDGET_H
#define CHECKEDCOLLECTIONWIDGET_H

#include <QWidget>
#include "pimcommonakonadi_export.h"

class QItemSelectionModel;
class QTreeView;
class KCheckableProxyModel;

namespace Akonadi {
class EntityTreeModel;
class Collection;
}

namespace PimCommon {
class CheckedCollectionWidgetPrivate;
/**
 * @brief The CheckedCollectionWidget class
 * @author Laurent Montel <montel@kde.org>
 */
class PIMCOMMONAKONADI_EXPORT CheckedCollectionWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CheckedCollectionWidget(const QString &mimetype, QWidget *parent = nullptr);
    ~CheckedCollectionWidget();

    Q_REQUIRED_RESULT Akonadi::EntityTreeModel *entityTreeModel() const;

    Q_REQUIRED_RESULT QTreeView *folderTreeView() const;

    Q_REQUIRED_RESULT QItemSelectionModel *selectionModel() const;

    Q_REQUIRED_RESULT KCheckableProxyModel *checkableProxy() const;

Q_SIGNALS:
    void collectionAdded(const Akonadi::Collection &, const Akonadi::Collection &);
    void collectionRemoved(const Akonadi::Collection &);

private:
    void slotSetCollectionFilter(const QString &filter);
    CheckedCollectionWidgetPrivate *const d;
};
}

#endif // CHECKEDCOLLECTIONWIDGET_H
