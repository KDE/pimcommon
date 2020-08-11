/*
  SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "customtoolsviewinterface.h"
using namespace PimCommon;
CustomToolsViewInterface::CustomToolsViewInterface(QWidget *parent)
    : QWidget(parent)
{
}

CustomToolsViewInterface::~CustomToolsViewInterface()
{
}

void CustomToolsViewInterface::setText(const QString &)
{
}

KToggleAction *CustomToolsViewInterface::action() const
{
    return nullptr;
}
