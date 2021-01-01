/*
  SPDX-FileCopyrightText: 2012-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "autocorrectionlistwidget.h"

#include <QKeyEvent>

using namespace PimCommon;

AutoCorrectionListWidget::AutoCorrectionListWidget(QWidget *parent)
    : QListWidget(parent)
{
}

AutoCorrectionListWidget::~AutoCorrectionListWidget()
{
}

void AutoCorrectionListWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Delete) {
        Q_EMIT deleteSelectedItems();
    }
    QListWidget::keyPressEvent(event);
}
