/*
  SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QWidget>
class QCheckBox;
namespace PimCommon
{
class AclManager;
class CollectionAclWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CollectionAclWidget(QWidget *parent = nullptr);
    ~CollectionAclWidget() override;

    [[nodiscard]] PimCommon::AclManager *aclManager() const;
    [[nodiscard]] bool recursive() const;
    void setEnableRecursiveCheckBox(bool enable);

private:
    void slotRecursivePermissionChanged();
    void slotCollectionCanBeAdministrated(bool b);
    PimCommon::AclManager *const mAclManager;
    QCheckBox *const mRecursiveChk;
};
}
