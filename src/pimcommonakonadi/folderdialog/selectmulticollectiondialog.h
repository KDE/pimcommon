/*
  SPDX-FileCopyrightText: 2013-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
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
