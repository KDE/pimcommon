/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "purposemenumessagewidget.h"
#include <KLocalizedString>

using namespace PimCommon;
PurposeMenuMessageWidget::PurposeMenuMessageWidget(QWidget *parent)
    : KMessageWidget(parent)
{
    setVisible(false);
    setCloseButtonVisible(true);
}

PurposeMenuMessageWidget::~PurposeMenuMessageWidget() = default;

void PurposeMenuMessageWidget::shareError(const QString &url)
{
    setMessageType(KMessageWidget::MessageType::Error);
    if (url.isEmpty()) {
        setText(i18n("File was shared."));
    } else {
        setText(i18n("<qt>You can find the new request at:<br /><a href='%1'>%1</a> </qt>", url));
    }
    animatedShow();
}

void PurposeMenuMessageWidget::shareSuccess(const QString &message)
{
    setMessageType(KMessageWidget::MessageType::Information);
    setText(i18n("There was a problem sharing the document: %1", message));
    animatedShow();
}

#include "moc_purposemenumessagewidget.cpp"
