/**
 *
 *  SPDX-FileCopyrightText: 2004 David Faure <faure@kde.org>
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "collectionaclpage.h"
#include "aclmanager.h"
#include "collectionaclwidget.h"
#include "imapaclattribute.h"
#include <Akonadi/Collection>
#include <KLocalizedString>
#include <QHBoxLayout>

using namespace PimCommon;

class PimCommon::CollectionAclPagePrivate
{
public:
    CollectionAclPagePrivate() = default;

    CollectionAclWidget *mCollectionAclWidget = nullptr;
};

CollectionAclPage::CollectionAclPage(QWidget *parent)
    : CollectionPropertiesPage(parent)
    , d(new PimCommon::CollectionAclPagePrivate)
{
    setObjectName(QStringLiteral("PimCommon::CollectionAclPage"));

    setPageTitle(i18n("Access Control"));
    init();
}

CollectionAclPage::~CollectionAclPage() = default;

void CollectionAclPage::init()
{
    auto layout = new QHBoxLayout(this);
    layout->setContentsMargins({});
    d->mCollectionAclWidget = new CollectionAclWidget(this);
    layout->addWidget(d->mCollectionAclWidget);
}

bool CollectionAclPage::canHandle(const Akonadi::Collection &collection) const
{
    return collection.hasAttribute<PimCommon::ImapAclAttribute>();
}

void CollectionAclPage::load(const Akonadi::Collection &collection)
{
    d->mCollectionAclWidget->aclManager()->setCollection(collection);
}

void CollectionAclPage::save(Akonadi::Collection &collection)
{
    d->mCollectionAclWidget->aclManager()->save(d->mCollectionAclWidget->recursive());

    // The collection dialog expects the changed collection to run
    // its own ItemModifyJob, so make him happy...
    const auto origCol = d->mCollectionAclWidget->aclManager()->collection();
    collection.addAttribute(origCol.attribute<PimCommon::ImapAclAttribute>()->clone());
}
