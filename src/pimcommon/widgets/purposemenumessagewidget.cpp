/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "purposemenumessagewidget.h"
using namespace PimCommon;
PurposeMenuMessageWidget::PurposeMenuMessageWidget(QWidget *parent)
    : KMessageWidget(parent)
{
}

PurposeMenuMessageWidget::~PurposeMenuMessageWidget() = default;

#include "moc_purposemenumessagewidget.cpp"
