/*
  SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "configurepluginswidget.h"
#include "configurepluginslistwidget.h"

#include <KConfigGroup>
#include <KLocalizedString>
#include <KMessageWidget>
#include <KSharedConfig>

#include <QSplitter>
#include <QTextEdit>
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

ConfigurePluginsWidget::~ConfigurePluginsWidget()
{
    writeConfig();
}

void ConfigurePluginsWidget::initLayout(ConfigurePluginsListWidget *configurePluginListWidget)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    mMessageWidget = new KMessageWidget(i18n("Restart is necessary for applying the changes."), this);
    mMessageWidget->setObjectName(QStringLiteral("mMessageWidget"));
    mMessageWidget->setCloseButtonVisible(false);
    mMessageWidget->setVisible(false);
    layout->addWidget(mMessageWidget);

    mSplitter = new QSplitter(this);
    mSplitter->setObjectName(QStringLiteral("splitter"));
    mSplitter->setChildrenCollapsible(false);
    layout->addWidget(mSplitter);

    if (!configurePluginListWidget) {
        mConfigureListWidget = new ConfigurePluginsListWidget(this);
    } else {
        mConfigureListWidget = configurePluginListWidget;
    }
    mConfigureListWidget->setObjectName(QStringLiteral("configureListWidget"));
    mSplitter->addWidget(mConfigureListWidget);

    mDescription = new QTextEdit(this);
    mDescription->setObjectName(QStringLiteral("description"));
    mDescription->setReadOnly(true);

    mSplitter->addWidget(mDescription);

    connect(mConfigureListWidget, &ConfigurePluginsListWidget::descriptionChanged, mDescription, &QTextEdit::setText);
    connect(mConfigureListWidget, &ConfigurePluginsListWidget::changed, this, &ConfigurePluginsWidget::slotConfigChanged);

    initialize();
    readConfig();
}

void ConfigurePluginsWidget::slotConfigChanged()
{
    mMessageWidget->animatedShow();
    Q_EMIT changed();
}

void ConfigurePluginsWidget::save()
{
    mConfigureListWidget->save();
}

void ConfigurePluginsWidget::defaults()
{
    mConfigureListWidget->defaults();
}

void ConfigurePluginsWidget::doLoadFromGlobalSettings()
{
    mConfigureListWidget->doLoadFromGlobalSettings();
}

void ConfigurePluginsWidget::doResetToDefaultsOther()
{
    mConfigureListWidget->doResetToDefaultsOther();
}

void ConfigurePluginsWidget::readConfig()
{
    KConfigGroup group(KSharedConfig::openConfig(), "ConfigurePluginsWidget");
    const QList<int> size = {400, 100};
    mSplitter->setSizes(group.readEntry("splitter", size));
}

void ConfigurePluginsWidget::writeConfig()
{
    KConfigGroup group(KSharedConfig::openConfig(), "ConfigurePluginsWidget");
    group.writeEntry("splitter", mSplitter->sizes());
}

void ConfigurePluginsWidget::initialize()
{
    mConfigureListWidget->initialize();
}
