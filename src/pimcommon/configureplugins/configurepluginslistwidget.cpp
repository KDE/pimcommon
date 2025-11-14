/*
  SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "configurepluginslistwidget.h"
#include "configurepluginstreewidgetdelegate.h"

#include <KLineEditEventHandler>
#include <KLocalizedString>
#include <KSharedConfig>
#include <KTreeWidgetSearchLine>
#include <KTreeWidgetSearchLineWidget>

#include <QAction>
#include <QHeaderView>
#include <QPushButton>
#include <QToolButton>
#include <QTreeWidget>
#include <QVBoxLayout>

using namespace Qt::Literals::StringLiterals;
using namespace PimCommon;
ConfigurePluginsListWidget::ConfigurePluginsListWidget(QWidget *parent)
    : TextAddonsWidgets::ConfigurePluginsWidget(parent)
{
}

ConfigurePluginsListWidget::~ConfigurePluginsListWidget() = default;

#include "moc_configurepluginslistwidget.cpp"
