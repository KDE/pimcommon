/*
  SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef ACLLISTVIEW_H
#define ACLLISTVIEW_H

#include <QListView>
#include "pimcommonakonadi_private_export.h"
namespace PimCommon {
class PIMCOMMONAKONADI_TESTS_EXPORT AclListView : public QListView
{
    Q_OBJECT
public:
    explicit AclListView(QWidget *parent = nullptr);
    ~AclListView() override;

public Q_SLOTS:
    void slotCollectionCanBeAdministrated(bool b);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void generalPaletteChanged();
    QColor mTextColor;
    bool mCanBeAdministrated = true;
};
}
#endif // ACLLISTVIEW_H
