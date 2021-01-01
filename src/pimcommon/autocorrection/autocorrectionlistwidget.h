/*
  SPDX-FileCopyrightText: 2012-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef AutoCorrectionListWidget_H
#define AutoCorrectionListWidget_H

#include <QListWidget>

namespace PimCommon {
class AutoCorrectionListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit AutoCorrectionListWidget(QWidget *parent = nullptr);
    ~AutoCorrectionListWidget() override;

protected:
    void keyPressEvent(QKeyEvent *event) override;

Q_SIGNALS:
    void deleteSelectedItems();
};
}

#endif // AutoCorrectionListWidget_H
