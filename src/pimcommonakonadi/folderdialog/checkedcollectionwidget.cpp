/*
  Copyright (c) 2013-2018 Montel Laurent <montel@kde.org>

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

#include "checkedcollectionwidget.h"
#include <RecursiveCollectionFilterProxyModel>
#include <CollectionFilterProxyModel>

#include <Monitor>
#include <EntityTreeModel>
#include <EntityRightsFilterModel>
#if (QT_VERSION < QT_VERSION_CHECK(5, 10, 0))
#include <KRecursiveFilterProxyModel>
#else
#include <QSortFilterProxyModel>
#endif

#include <KCheckableProxyModel>
#include <QLineEdit>
#include <KLocalizedString>

#include <QVBoxLayout>
#include <QTreeView>

using namespace PimCommon;

class PimCommon::CheckedCollectionWidgetPrivate
{
public:
    CheckedCollectionWidgetPrivate()
        : mFolderView(nullptr)
        , mSelectionModel(nullptr)
        , mCheckProxy(nullptr)
        , mCollectionFilter(nullptr)
        , mEntityTreeModel(nullptr)
    {
    }

    QTreeView *mFolderView = nullptr;
    QItemSelectionModel *mSelectionModel = nullptr;
    KCheckableProxyModel *mCheckProxy = nullptr;
#if (QT_VERSION < QT_VERSION_CHECK(5, 10, 0))
    KRecursiveFilterProxyModel *mCollectionFilter = nullptr;
#else
    QSortFilterProxyModel *mCollectionFilter = nullptr;
#endif

    Akonadi::EntityTreeModel *mEntityTreeModel = nullptr;
};

CheckedCollectionWidget::CheckedCollectionWidget(const QString &mimetype, QWidget *parent)
    : QWidget(parent)
    , d(new PimCommon::CheckedCollectionWidgetPrivate)
{
    QVBoxLayout *vbox = new QVBoxLayout(this);
    vbox->setMargin(0);

    // Create a new change recorder.
    Akonadi::Monitor *monitor = new Akonadi::Monitor(this);
    monitor->setObjectName(QStringLiteral("CheckedCollectionWidgetMonitor"));
    monitor->fetchCollection(true);
    monitor->setAllMonitored(true);
    monitor->setMimeTypeMonitored(mimetype);
    connect(monitor, &Akonadi::Monitor::collectionAdded, this, &CheckedCollectionWidget::collectionAdded);
    connect(monitor, &Akonadi::Monitor::collectionRemoved, this, &CheckedCollectionWidget::collectionRemoved);

    d->mEntityTreeModel = new Akonadi::EntityTreeModel(monitor, this);
    // Set the model to show only collections, not items.
    d->mEntityTreeModel->setItemPopulationStrategy(Akonadi::EntityTreeModel::NoItemPopulation);

    Akonadi::CollectionFilterProxyModel *mimeTypeProxy = new Akonadi::CollectionFilterProxyModel(this);
    mimeTypeProxy->setExcludeVirtualCollections(true);
    mimeTypeProxy->addMimeTypeFilters(QStringList() << mimetype);
    mimeTypeProxy->setSourceModel(d->mEntityTreeModel);

    // Create the Check proxy model.
    d->mSelectionModel = new QItemSelectionModel(mimeTypeProxy);
    d->mCheckProxy = new KCheckableProxyModel(this);
    d->mCheckProxy->setSelectionModel(d->mSelectionModel);
    d->mCheckProxy->setSourceModel(mimeTypeProxy);
#if (QT_VERSION < QT_VERSION_CHECK(5, 10, 0))
    d->mCollectionFilter = new KRecursiveFilterProxyModel(this);
    d->mCollectionFilter->setDynamicSortFilter(true);
#else
    d->mCollectionFilter = new QSortFilterProxyModel(this);
    d->mCollectionFilter->setRecursiveFilteringEnabled(true);
#endif
    d->mCollectionFilter->setSourceModel(d->mCheckProxy);
    d->mCollectionFilter->setFilterCaseSensitivity(Qt::CaseInsensitive);

    QLineEdit *searchLine = new QLineEdit(this);
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

CheckedCollectionWidget::~CheckedCollectionWidget()
{
    delete d;
}

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
