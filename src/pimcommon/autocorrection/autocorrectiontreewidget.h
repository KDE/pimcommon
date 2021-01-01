/*
  SPDX-FileCopyrightText: 2012-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef AutoCorrectionTreeWidget_H
#define AutoCorrectionTreeWidget_H

#include <QTreeWidget>

namespace PimCommon {
class AutoCorrectionTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit AutoCorrectionTreeWidget(QWidget *parent = nullptr);
    ~AutoCorrectionTreeWidget() override;

protected:
    void keyPressEvent(QKeyEvent *event) override;

Q_SIGNALS:
    void deleteSelectedItems();
};
}

#endif // AutoCorrectionTreeWidget_H
