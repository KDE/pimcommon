/*
  SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "configurepluginswidget.h"
using namespace Qt::Literals::StringLiterals;

#include "configurepluginslistwidget.h"

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

ConfigurePluginsWidget::ConfigurePluginsWidget(ConfigurePluginsListWidget *configurePluginListWidget, QWidget *parent)
    : QWidget(parent)
{
    initLayout(configurePluginListWidget);
}

ConfigurePluginsWidget::~ConfigurePluginsWidget() = default;

void ConfigurePluginsWidget::initLayout(ConfigurePluginsListWidget *configurePluginListWidget)
{
    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins({});

    mMessageWidget = new KMessageWidget(i18n("Restart is necessary for applying the changes."), this);
    mMessageWidget->setObjectName("mMessageWidget"_L1);
    mMessageWidget->setCloseButtonVisible(false);
    mMessageWidget->setVisible(false);
    mMessageWidget->setPosition(KMessageWidget::Header);
    layout->addWidget(mMessageWidget);

    if (!configurePluginListWidget) {
        mConfigureListWidget = new ConfigurePluginsListWidget(this);
    } else {
        mConfigureListWidget = configurePluginListWidget;
    }
    mConfigureListWidget->setObjectName("configureListWidget"_L1);
    layout->addWidget(mConfigureListWidget);

    connect(mConfigureListWidget, &ConfigurePluginsListWidget::changed, this, &ConfigurePluginsWidget::slotConfigChanged);

    initialize();
}

void ConfigurePluginsWidget::slotConfigChanged()
{
    mMessageWidget->animatedShow();
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
    mMessageWidget->animatedHide();
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
