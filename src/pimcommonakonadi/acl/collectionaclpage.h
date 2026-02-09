/*!
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
/*!
 * \class PimCommon::CollectionAclPage
 * \brief The CollectionAclPage class provides an "Access Control" tab for collection properties
 * \inmodule PimCommonAkonadi
 * \inheaderfile PimCommonAkonadi/CollectionAclPage
 * \author David Faure <faure@kde.org>
 */
class PIMCOMMONAKONADI_EXPORT CollectionAclPage : public Akonadi::CollectionPropertiesPage
{
    Q_OBJECT

public:
    /*!
     * Constructs a CollectionAclPage.
     * @param parent The parent widget
     */
    explicit CollectionAclPage(QWidget *parent = nullptr);
    /*!
     * Destructs the CollectionAclPage.
     */
    ~CollectionAclPage() override;

    /*!
     * Loads the ACL information from a collection.
     * @param collection The Akonadi collection to load ACL from
     */
    void load(const Akonadi::Collection &collection) override;
    /*!
     * Saves the ACL information to a collection.
     * @param collection The Akonadi collection to save ACL to
     */
    void save(Akonadi::Collection &collection) override;

    /*!
     * Checks if this page can handle the given collection.
     * @param collection The collection to check
     * @return true if this page can handle the collection, false otherwise
     */
    [[nodiscard]] bool canHandle(const Akonadi::Collection &collection) const override;

protected:
    /*!
     * Initializes the page UI and connects signals.
     */
    void init();

private:
    std::unique_ptr<CollectionAclPagePrivate> const d;
};
AKONADI_COLLECTION_PROPERTIES_PAGE_FACTORY(CollectionAclPageFactory, CollectionAclPage)
}
