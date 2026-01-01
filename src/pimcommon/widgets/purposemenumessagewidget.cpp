/*
  SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "purposemenumessagewidget.h"
#include <QDesktopServices>
#include <QUrl>

using namespace PimCommon;
PurposeMenuMessageWidget::PurposeMenuMessageWidget(QWidget *parent)
    : KMessageWidget(parent)
{
    setVisible(false);
    setCloseButtonVisible(true);
    connect(this, &KMessageWidget::linkActivated, this, [](const QString &contents) {
        QDesktopServices::openUrl(QUrl(contents));
    });
}

PurposeMenuMessageWidget::~PurposeMenuMessageWidget() = default;

void PurposeMenuMessageWidget::slotShareError(const QString &message)
{
    setMessageType(KMessageWidget::MessageType::Error);
    setText(message);
    animatedShow();
}

void PurposeMenuMessageWidget::slotShareSuccess(const QString &message)
{
    setMessageType(KMessageWidget::MessageType::Information);
    setText(message);
    animatedShow();
}

#include "moc_purposemenumessagewidget.cpp"
