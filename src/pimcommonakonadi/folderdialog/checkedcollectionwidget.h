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
/*!
 * \class CheckedCollectionWidget
 * \brief The CheckedCollectionWidget class provides a widget for selecting and checking Akonadi collections
 * \inmodule PimCommonAkonadi
 * \inheaderfile PimCommonAkonadi/CheckedCollectionWidget
 * \author Laurent Montel <montel@kde.org>
 */
class PIMCOMMONAKONADI_EXPORT CheckedCollectionWidget : public QWidget
{
    Q_OBJECT
public:
    /*!
     * Constructs a CheckedCollectionWidget.
     * @param mimetype The MIME type to filter collections
     * @param parent The parent widget
     */
    explicit CheckedCollectionWidget(const QString &mimetype, QWidget *parent = nullptr);
    /*!
     * Destructs the CheckedCollectionWidget.
     */
    ~CheckedCollectionWidget() override;

    /*!
     * Returns the entity tree model.
     * @return The Akonadi::EntityTreeModel
     */
    [[nodiscard]] Akonadi::EntityTreeModel *entityTreeModel() const;

    /*!
     * Returns the folder tree view widget.
     * @return The QTreeView for displaying folders
     */
    [[nodiscard]] QTreeView *folderTreeView() const;

    /*!
     * Returns the selection model.
     * @return The QItemSelectionModel
     */
    [[nodiscard]] QItemSelectionModel *selectionModel() const;

    /*!
     * Returns the checkable proxy model.
     * @return The KCheckableProxyModel
     */
    [[nodiscard]] KCheckableProxyModel *checkableProxy() const;

Q_SIGNALS:
    /*!
     * Emitted when a collection is added.
     * @param collection The added collection
     * @param parent The parent collection
     */
    void collectionAdded(const Akonadi::Collection &, const Akonadi::Collection &);
    /*!
     * Emitted when a collection is removed.
     * @param collection The removed collection
     */
    void collectionRemoved(const Akonadi::Collection &);

private:
    PIMCOMMONAKONADI_NO_EXPORT void slotSetCollectionFilter(const QString &filter);
    std::unique_ptr<CheckedCollectionWidgetPrivate> const d;
};
}
