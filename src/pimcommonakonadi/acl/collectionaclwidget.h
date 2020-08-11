/*
  SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef COLLECTIONACLWIDGET_H
#define COLLECTIONACLWIDGET_H

#include <QWidget>
class QCheckBox;
namespace PimCommon {
class AclManager;
class CollectionAclWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CollectionAclWidget(QWidget *parent = nullptr);
    ~CollectionAclWidget();

    Q_REQUIRED_RESULT PimCommon::AclManager *aclManager() const;
    Q_REQUIRED_RESULT bool recursive() const;
    void setEnableRecursiveCheckBox(bool enable);

private Q_SLOTS:
    void slotRecursivePermissionChanged();
    void slotCollectionCanBeAdministrated(bool b);

private:
    PimCommon::AclManager *mAclManager = nullptr;
    QCheckBox *mRecursiveChk = nullptr;
};
}

#endif // COLLECTIONACLWIDGET_H
