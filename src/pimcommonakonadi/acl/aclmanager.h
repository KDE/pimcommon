/*
 * SPDX-FileCopyrightText: 2010 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
 * SPDX-FileCopyrightText: 2010 Tobias Koenig <tokoe@kdab.com>
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

#include "pimcommonakonadi_private_export.h"

#include <Akonadi/Collection>

#include <QObject>

class QAbstractItemModel;
class QAction;
class QItemSelectionModel;

namespace PimCommon
{
class PIMCOMMONAKONADI_TESTS_EXPORT AclManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(Akonadi::Collection collection READ collection WRITE setCollection NOTIFY collectionChanged)
    Q_PROPERTY(QAbstractItemModel *model READ model)
    Q_PROPERTY(QItemSelectionModel *selectionModel READ selectionModel)
    Q_PROPERTY(QAction *addAction READ addAction)
    Q_PROPERTY(QAction *editAction READ editAction)
    Q_PROPERTY(QAction *deleteAction READ deleteAction)

public:
    /**
     * Creates a new ACL manager.
     *
     * @param parent The parent object.
     */
    explicit AclManager(QObject *parent = nullptr);

    /**
     * Destroys the ACL manager.
     */
    ~AclManager() override;

    /**
     * Sets the @p collection whose ACL will be managed.
     */
    void setCollection(const Akonadi::Collection &collection);

    /**
     * Sets the @p collection whose ACL are managed.
     */
    Q_REQUIRED_RESULT Akonadi::Collection collection() const;

    /**
     * Returns the model that represents the ACL of the managed collection.
     */
    Q_REQUIRED_RESULT QAbstractItemModel *model() const;

    /**
     * Returns the selection model that is used by the manager to select the
     * ACL entry to work on.
     */
    Q_REQUIRED_RESULT QItemSelectionModel *selectionModel() const;

    /**
     * Returns the action that handles adding new ACL entries.
     */
    Q_REQUIRED_RESULT QAction *addAction() const;

    /**
     * Returns the action that handles editing the currently selected ACL entry.
     */
    Q_REQUIRED_RESULT QAction *editAction() const;

    /**
     * Returns the action that handles deleting the currently selected ACL entry.
     */
    Q_REQUIRED_RESULT QAction *deleteAction() const;

    void setChanged(bool b);
public Q_SLOTS:
    /**
     * Saves the changes of the ACL back to the collection.
     */
    void save(bool recursive);

Q_SIGNALS:
    /**
     * This signal is emitted whenever the collection whose ACL will
     * be managed has changed.
     */
    void collectionChanged(const Akonadi::Collection &collection);

    void collectionCanBeAdministrated(bool canAdmin);

private:
    //@cond PRIVATE
    class Private;
    Private *const d;
    //@endcond
};
}

