/*
  Copyright (c) 2013-2020 Laurent Montel <montel@kde.org>

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

#ifndef SELECTMULTICOLLECTIONDIALOG_H
#define SELECTMULTICOLLECTIONDIALOG_H
#include "pimcommonakonadi_export.h"
#include <QDialog>
#include <Collection>

namespace PimCommon {
class SelectMultiCollectionDialogPrivate;
/**
 * @brief The SelectMultiCollectionDialog class
 * @author Laurent Montel <montel@kde.org>
 */
class PIMCOMMONAKONADI_EXPORT SelectMultiCollectionDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SelectMultiCollectionDialog(const QString &mimetype, const QList<Akonadi::Collection::Id> &selectedCollection, QWidget *parent = nullptr);
    explicit SelectMultiCollectionDialog(const QString &mimetype, QWidget *parent = nullptr);
    ~SelectMultiCollectionDialog();

    Q_REQUIRED_RESULT QVector<Akonadi::Collection> selectedCollection() const;

private:
    void initialize(const QString &mimetype, const QList<Akonadi::Collection::Id> &selectedCollection = QList<Akonadi::Collection::Id>());
    void writeConfig();
    void readConfig();
    SelectMultiCollectionDialogPrivate *const d;
};
}

#endif // SELECTMULTICOLLECTIONDIALOG_H
