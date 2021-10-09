/**
 * folderdialogacltab.h
 *
 *  SPDX-FileCopyrightText: 2004 David Faure <faure@kde.org>
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

#include "pimcommonakonadi_export.h"
#include <Akonadi/CollectionPropertiesPage>

namespace PimCommon
{
class CollectionAclPagePrivate;
/**
 * "Access Control" tab in the folder dialog
 */
class PIMCOMMONAKONADI_EXPORT CollectionAclPage : public Akonadi::CollectionPropertiesPage
{
    Q_OBJECT

public:
    explicit CollectionAclPage(QWidget *parent = nullptr);
    ~CollectionAclPage() override;

    void load(const Akonadi::Collection &collection) override;
    void save(Akonadi::Collection &collection) override;

    Q_REQUIRED_RESULT bool canHandle(const Akonadi::Collection &collection) const override;

protected:
    void init();

private:
    std::unique_ptr<CollectionAclPagePrivate> const d;
};
AKONADI_COLLECTION_PROPERTIES_PAGE_FACTORY(CollectionAclPageFactory, CollectionAclPage)
}

