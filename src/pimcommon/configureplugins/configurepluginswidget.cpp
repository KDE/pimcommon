/*
  SPDX-FileCopyrightText: 2016-2024 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "configurepluginswidget.h"
using namespace Qt::Literals::StringLiterals;

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
    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins({});

    mMessageWidget = new KMessageWidget(i18n("Restart is necessary for applying the changes."), this);
    mMessageWidget->setObjectName("mMessageWidget"_L1);
    mMessageWidget->setCloseButtonVisible(false);
    mMessageWidget->setVisible(false);
    mMessageWidget->setPosition(KMessageWidget::Header);
    layout->addWidget(mMessageWidget);

    mSplitter = new QSplitter(this);
    mSplitter->setObjectName("splitter"_L1);
    mSplitter->setChildrenCollapsible(false);
    layout->addWidget(mSplitter);

    if (!configurePluginListWidget) {
        mConfigureListWidget = new ConfigurePluginsListWidget(this);
    } else {
        mConfigureListWidget = configurePluginListWidget;
    }
    mConfigureListWidget->setObjectName("configureListWidget"_L1);
    mSplitter->addWidget(mConfigureListWidget);

    mDescription = new QTextEdit(this);
    mDescription->setObjectName("description"_L1);
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
    KConfigGroup group(KSharedConfig::openStateConfig(), QStringLiteral("ConfigurePluginsWidget"));
    const QList<int> size = {400, 100};
    mSplitter->setSizes(group.readEntry("splitter", size));
}

void ConfigurePluginsWidget::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), QStringLiteral("ConfigurePluginsWidget"));
    group.writeEntry("splitter", mSplitter->sizes());
}

void ConfigurePluginsWidget::initialize()
{
    mConfigureListWidget->initialize();
}

#include "moc_configurepluginswidget.cpp"
