/*
  SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "configurepluginswidget.h"
using namespace Qt::Literals::StringLiterals;

#include <KConfigGroup>
#include <KLocalizedString>
#include <KMessageWidget>
#include <KSharedConfig>

#include <QVBoxLayout>

using namespace PimCommon;

ConfigurePluginsWidget::ConfigurePluginsWidget(QWidget *parent)
    : QWidget(parent)
{
    initLayout();
}

ConfigurePluginsWidget::ConfigurePluginsWidget(TextAddonsWidgets::ConfigurePluginsWidget *configurePluginListWidget, QWidget *parent)
    : QWidget(parent)
{
    initLayout(configurePluginListWidget);
}

ConfigurePluginsWidget::~ConfigurePluginsWidget() = default;

void ConfigurePluginsWidget::initLayout(TextAddonsWidgets::ConfigurePluginsWidget *configurePluginListWidget)
{
    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins({});

    if (!configurePluginListWidget) {
        mConfigureListWidget = new TextAddonsWidgets::ConfigurePluginsWidget(this);
    } else {
        mConfigureListWidget = configurePluginListWidget;
    }
    mConfigureListWidget->setObjectName("configureListWidget"_L1);
    layout->addWidget(mConfigureListWidget);

    connect(mConfigureListWidget, &TextAddonsWidgets::ConfigurePluginsWidget::changed, this, &ConfigurePluginsWidget::slotConfigChanged);

    initialize();
}

void ConfigurePluginsWidget::slotConfigChanged()
{
    Q_EMIT wasChanged(true);
}

void ConfigurePluginsWidget::save()
{
    mConfigureListWidget->save();
    Q_EMIT wasChanged(false);
}

void ConfigurePluginsWidget::defaults()
{
    mConfigureListWidget->defaults();
}

void ConfigurePluginsWidget::doLoadFromGlobalSettings()
{
    mConfigureListWidget->doLoadFromGlobalSettings();
    Q_EMIT wasChanged(false);
}

void ConfigurePluginsWidget::doResetToDefaultsOther()
{
    mConfigureListWidget->doResetToDefaultsOther();
}

void ConfigurePluginsWidget::initialize()
{
    mConfigureListWidget->initialize();
}

#include "moc_configurepluginswidget.cpp"
