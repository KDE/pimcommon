/*
  Copyright (c) 2016 Montel Laurent <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License, version 2, as
  published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "configurepluginslistwidget.h"

#include <KConfigGroup>
#include <KSharedConfig>
#include <KLocalizedString>

#include <QHBoxLayout>
#include <QLabel>
#include <QTreeWidget>

using namespace PimCommon;
ConfigurePluginsListWidget::ConfigurePluginsListWidget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setMargin(0);

    mListWidget = new QTreeWidget(this);
    mListWidget->setSortingEnabled(true);
    mListWidget->sortItems(0, Qt::AscendingOrder);
    mListWidget->setObjectName(QStringLiteral("listwidget"));
    mListWidget->setHeaderHidden(true);
    mListWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    connect(mListWidget, &QTreeWidget::itemSelectionChanged, this, &ConfigurePluginsListWidget::slotItemSelectionChanged);
    connect(mListWidget, &QTreeWidget::itemChanged, this, &ConfigurePluginsListWidget::slotItemChanged);

    mainLayout->addWidget(mListWidget);
}

ConfigurePluginsListWidget::~ConfigurePluginsListWidget()
{
}

void ConfigurePluginsListWidget::slotItemChanged(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(item);
    if (column == 0) {
        Q_EMIT changed();
    }
}

void ConfigurePluginsListWidget::slotItemSelectionChanged()
{
    QTreeWidgetItem *item = mListWidget->currentItem();
    if (PluginItem *pluginItem = dynamic_cast<PluginItem *>(item)) {
        Q_EMIT descriptionChanged(pluginItem->mDescription);
    }
}

void ConfigurePluginsListWidget::save()
{
}

void ConfigurePluginsListWidget::doLoadFromGlobalSettings()
{
    initialize();
}

void ConfigurePluginsListWidget::doResetToDefaultsOther()
{
}

void ConfigurePluginsListWidget::initialize()
{
}
