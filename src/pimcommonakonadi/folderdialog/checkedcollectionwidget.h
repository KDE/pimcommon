/*
  SPDX-FileCopyrightText: 2013-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "pimcommonakonadi_export.h"
#include <QWidget>

class QItemSelectionModel;
class QTreeView;
class KCheckableProxyModel;

namespace Akonadi
{
class EntityTreeModel;
class Collection;
}

namespace PimCommon
{
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
    ~CheckedCollectionWidget() override;

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

