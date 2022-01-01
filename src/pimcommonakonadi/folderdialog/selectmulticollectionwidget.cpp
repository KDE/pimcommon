/*
  SPDX-FileCopyrightText: 2013-2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "selectmulticollectionwidget.h"
#include "folderdialog/checkedcollectionwidget.h"

#include <Akonadi/CollectionFilterProxyModel>
#include <Akonadi/EntityTreeModel>

#include <KCheckableProxyModel>

#include <QTreeView>
#include <QVBoxLayout>

using namespace PimCommon;
SelectMultiCollectionWidget::SelectMultiCollectionWidget(const QString &mimetype, QWidget *parent)
    : QWidget(parent)
{
    initialize(mimetype);
}

SelectMultiCollectionWidget::SelectMultiCollectionWidget(const QString &mimetype, const QList<Akonadi::Collection::Id> &selectedCollection, QWidget *parent)
    : QWidget(parent)
    , mListCollection(selectedCollection)
{
    initialize(mimetype);
}

SelectMultiCollectionWidget::~SelectMultiCollectionWidget() = default;

void SelectMultiCollectionWidget::initialize(const QString &mimetype)
{
    auto vbox = new QVBoxLayout(this);
    vbox->setContentsMargins({});

    mCheckedCollectionWidget = new PimCommon::CheckedCollectionWidget(mimetype);

    connect(mCheckedCollectionWidget, &PimCommon::CheckedCollectionWidget::collectionAdded, this, &SelectMultiCollectionWidget::slotCollectionsTreeFetched);
    connect(mCheckedCollectionWidget, &PimCommon::CheckedCollectionWidget::collectionRemoved, this, &SelectMultiCollectionWidget::slotCollectionsTreeFetched);

    connect(mCheckedCollectionWidget->entityTreeModel(),
            &Akonadi::EntityTreeModel::collectionTreeFetched,
            this,
            &SelectMultiCollectionWidget::slotCollectionsTreeFetched);
    vbox->addWidget(mCheckedCollectionWidget);
}

void SelectMultiCollectionWidget::updateStatus(const QModelIndex &parent)
{
    const int nbCol = mCheckedCollectionWidget->checkableProxy()->rowCount(parent);
    for (int i = 0; i < nbCol; ++i) {
        const QModelIndex child = mCheckedCollectionWidget->checkableProxy()->index(i, 0, parent);

        const auto col = mCheckedCollectionWidget->checkableProxy()->data(child, Akonadi::EntityTreeModel::CollectionRole).value<Akonadi::Collection>();

        if (mListCollection.contains(col.id())) {
            mCheckedCollectionWidget->checkableProxy()->setData(child, Qt::Checked, Qt::CheckStateRole);
        }
        updateStatus(child);
    }
}

void SelectMultiCollectionWidget::slotCollectionsTreeFetched()
{
    if (!mListCollection.isEmpty()) {
        updateStatus(QModelIndex());
    }
    mCheckedCollectionWidget->folderTreeView()->expandAll();
}

QVector<Akonadi::Collection> SelectMultiCollectionWidget::selectedCollection(const QModelIndex &parent) const
{
    QVector<Akonadi::Collection> lst;

    const int nbCol = mCheckedCollectionWidget->checkableProxy()->rowCount(parent);
    for (int i = 0; i < nbCol; ++i) {
        const QModelIndex child = mCheckedCollectionWidget->checkableProxy()->index(i, 0, parent);

        const auto col = mCheckedCollectionWidget->checkableProxy()->data(child, Akonadi::EntityTreeModel::CollectionRole).value<Akonadi::Collection>();

        if (mCheckedCollectionWidget->checkableProxy()->data(child, Qt::CheckStateRole).toInt()) {
            lst << col;
        }
        lst << selectedCollection(child);
    }
    return lst;
}
