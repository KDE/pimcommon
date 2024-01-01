/*
  SPDX-FileCopyrightText: 2015-2024 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "pimcommonakonadi_private_export.h"
#include <QListView>
namespace PimCommon
{
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
