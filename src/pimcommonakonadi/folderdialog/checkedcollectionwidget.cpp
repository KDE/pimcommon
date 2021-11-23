/*
  SPDX-FileCopyrightText: 2013-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "checkedcollectionwidget.h"
#include <Akonadi/CollectionFilterProxyModel>

#include <Akonadi/EntityTreeModel>
#include <Akonadi/Monitor>
#include <QSortFilterProxyModel>

#include <KCheckableProxyModel>
#include <KLocalizedString>
#include <QLineEdit>

#include <QTreeView>
#include <QVBoxLayout>

using namespace PimCommon;

class PimCommon::CheckedCollectionWidgetPrivate
{
public:
    CheckedCollectionWidgetPrivate() = default;

    QTreeView *mFolderView = nullptr;
    QItemSelectionModel *mSelectionModel = nullptr;
    KCheckableProxyModel *mCheckProxy = nullptr;
    QSortFilterProxyModel *mCollectionFilter = nullptr;

    Akonadi::EntityTreeModel *mEntityTreeModel = nullptr;
};

CheckedCollectionWidget::CheckedCollectionWidget(const QString &mimetype, QWidget *parent)
    : QWidget(parent)
    , d(new PimCommon::CheckedCollectionWidgetPrivate)
{
    auto vbox = new QVBoxLayout(this);
    vbox->setContentsMargins({});

    // Create a new change recorder.
    auto monitor = new Akonadi::Monitor(this);
    monitor->setObjectName(QStringLiteral("CheckedCollectionWidgetMonitor"));
    monitor->fetchCollection(true);
    monitor->setAllMonitored(true);
    monitor->setMimeTypeMonitored(mimetype);
    connect(monitor, &Akonadi::Monitor::collectionAdded, this, &CheckedCollectionWidget::collectionAdded);
    connect(monitor, &Akonadi::Monitor::collectionRemoved, this, &CheckedCollectionWidget::collectionRemoved);

    d->mEntityTreeModel = new Akonadi::EntityTreeModel(monitor, this);
    // Set the model to show only collections, not items.
    d->mEntityTreeModel->setItemPopulationStrategy(Akonadi::EntityTreeModel::NoItemPopulation);

    auto mimeTypeProxy = new Akonadi::CollectionFilterProxyModel(this);
    mimeTypeProxy->setExcludeVirtualCollections(true);
    mimeTypeProxy->addMimeTypeFilters({mimetype});
    mimeTypeProxy->setSourceModel(d->mEntityTreeModel);

    // Create the Check proxy model.
    d->mSelectionModel = new QItemSelectionModel(mimeTypeProxy);
    d->mCheckProxy = new KCheckableProxyModel(this);
    d->mCheckProxy->setSelectionModel(d->mSelectionModel);
    d->mCheckProxy->setSourceModel(mimeTypeProxy);
    d->mCollectionFilter = new QSortFilterProxyModel(this);
    d->mCollectionFilter->setRecursiveFilteringEnabled(true);
    d->mCollectionFilter->setSourceModel(d->mCheckProxy);
    d->mCollectionFilter->setFilterCaseSensitivity(Qt::CaseInsensitive);

    auto searchLine = new QLineEdit(this);
    searchLine->setPlaceholderText(i18n("Search..."));
    searchLine->setClearButtonEnabled(true);
    connect(searchLine, &QLineEdit::textChanged, this, &CheckedCollectionWidget::slotSetCollectionFilter);

    vbox->addWidget(searchLine);

    d->mFolderView = new QTreeView;
    d->mFolderView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    d->mFolderView->setAlternatingRowColors(true);
    d->mFolderView->setModel(d->mCollectionFilter);

    vbox->addWidget(d->mFolderView);
}

CheckedCollectionWidget::~CheckedCollectionWidget() = default;

Akonadi::EntityTreeModel *CheckedCollectionWidget::entityTreeModel() const
{
    return d->mEntityTreeModel;
}

QTreeView *CheckedCollectionWidget::folderTreeView() const
{
    return d->mFolderView;
}

QItemSelectionModel *CheckedCollectionWidget::selectionModel() const
{
    return d->mSelectionModel;
}

KCheckableProxyModel *CheckedCollectionWidget::checkableProxy() const
{
    return d->mCheckProxy;
}

void CheckedCollectionWidget::slotSetCollectionFilter(const QString &filter)
{
    d->mCollectionFilter->setFilterWildcard(filter);
    d->mFolderView->expandAll();
}
