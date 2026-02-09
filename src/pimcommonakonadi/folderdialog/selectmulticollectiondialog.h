/*
  SPDX-FileCopyrightText: 2013-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "pimcommonakonadi_export.h"
#include <Akonadi/Collection>
#include <QDialog>

namespace PimCommon
{
class SelectMultiCollectionDialogPrivate;
/*!
 * \class PimCommon::SelectMultiCollectionDialog
 * \brief The SelectMultiCollectionDialog class provides a dialog for selecting multiple Akonadi collections
 * \inmodule PimCommonAkonadi
 * \inheaderfile PimCommonAkonadi/SelectMultiCollectionDialog
 * \author Laurent Montel <montel@kde.org>
 */
class PIMCOMMONAKONADI_EXPORT SelectMultiCollectionDialog : public QDialog
{
    Q_OBJECT
public:
    /*!
     * Constructs a SelectMultiCollectionDialog with pre-selected collections.
     * @param mimetype The MIME type to filter collections
     * @param selectedCollection The list of pre-selected collection IDs
     * @param parent The parent widget
     */
    explicit SelectMultiCollectionDialog(const QString &mimetype, const QList<Akonadi::Collection::Id> &selectedCollection, QWidget *parent = nullptr);
    /*!
     * Constructs a SelectMultiCollectionDialog.
     * @param mimetype The MIME type to filter collections
     * @param parent The parent widget
     */
    explicit SelectMultiCollectionDialog(const QString &mimetype, QWidget *parent = nullptr);
    /*!
     * Destructs the SelectMultiCollectionDialog.
     */
    ~SelectMultiCollectionDialog() override;

    /*!
     * Returns the list of selected collections.
     * @return A list of selected Akonadi collections
     */
    [[nodiscard]] QList<Akonadi::Collection> selectedCollection() const;

private:
    PIMCOMMONAKONADI_NO_EXPORT void initialize(const QString &mimetype,
                                               const QList<Akonadi::Collection::Id> &selectedCollection = QList<Akonadi::Collection::Id>());
    PIMCOMMONAKONADI_NO_EXPORT void writeConfig();
    PIMCOMMONAKONADI_NO_EXPORT void readConfig();
    std::unique_ptr<SelectMultiCollectionDialogPrivate> const d;
};
}
