/*
  SPDX-FileCopyrightText: 2013-2026 Laurent Montel <montel@kde.org>

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

    [[nodiscard]] Akonadi::EntityTreeModel *entityTreeModel() const;

    [[nodiscard]] QTreeView *folderTreeView() const;

    [[nodiscard]] QItemSelectionModel *selectionModel() const;

    [[nodiscard]] KCheckableProxyModel *checkableProxy() const;

Q_SIGNALS:
    void collectionAdded(const Akonadi::Collection &, const Akonadi::Collection &);
    void collectionRemoved(const Akonadi::Collection &);

private:
    PIMCOMMONAKONADI_NO_EXPORT void slotSetCollectionFilter(const QString &filter);
    std::unique_ptr<CheckedCollectionWidgetPrivate> const d;
};
}
