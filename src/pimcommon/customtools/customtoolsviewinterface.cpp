/*
  SPDX-FileCopyrightText: 2015-2024 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "customtoolsviewinterface.h"
using namespace PimCommon;
CustomToolsViewInterface::CustomToolsViewInterface(QWidget *parent)
    : QWidget(parent)
{
}

CustomToolsViewInterface::~CustomToolsViewInterface() = default;

void CustomToolsViewInterface::setText(const QString &)
{
}

KToggleAction *CustomToolsViewInterface::action() const
{
    return nullptr;
}

#include "moc_customtoolsviewinterface.cpp"
