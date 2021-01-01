/*
  SPDX-FileCopyrightText: 2013-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef SELECTMULTICOLLECTIONWIDGET_H
#define SELECTMULTICOLLECTIONWIDGET_H

#include <QWidget>
#include <Collection>
#include <QModelIndex>

namespace PimCommon {
class CheckedCollectionWidget;
class SelectMultiCollectionWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SelectMultiCollectionWidget(const QString &mimetype, const QList<Akonadi::Collection::Id> &selectedCollection, QWidget *parent = nullptr);
    explicit SelectMultiCollectionWidget(const QString &mimetype, QWidget *parent = nullptr);
    ~SelectMultiCollectionWidget();

    Q_REQUIRED_RESULT QVector<Akonadi::Collection> selectedCollection(const QModelIndex &parent = QModelIndex()) const;

private:
    void slotCollectionsTreeFetched();
    void initialize(const QString &mimetype);
    void updateStatus(const QModelIndex &parent);
    PimCommon::CheckedCollectionWidget *mCheckedCollectionWidget = nullptr;
    QList<Akonadi::Collection::Id> mListCollection;
};
}

#endif // SELECTMULTICOLLECTIONWIDGET_H
