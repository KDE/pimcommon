/*
  SPDX-FileCopyrightText: 2015-2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "customtoolspluginmanager.h"
#include "customtoolsplugin.h"

#include <KPluginFactory>
#include <KPluginMetaData>

#include <QDebug>
#include <QFileInfo>
#include <QSet>

using namespace PimCommon;

class CustomToolsPluginInfo
{
public:
    Q_REQUIRED_RESULT QString saveName() const;

    KPluginMetaData metaData;
    PimCommon::CustomToolsPlugin *plugin = nullptr;
};

QString CustomToolsPluginInfo::saveName() const
{
    return QFileInfo(metaData.fileName()).baseName();
}

namespace
{
QString pluginVersion()
{
    return QStringLiteral("1.0");
}
}

class PimCommon::CustomToolsPluginManagerPrivate
{
public:
    CustomToolsPluginManagerPrivate(CustomToolsPluginManager *qq)
        : q(qq)
    {
    }

    Q_REQUIRED_RESULT QVector<PimCommon::CustomToolsPlugin *> pluginsList() const;
    void initializePluginList();
    void loadPlugin(CustomToolsPluginInfo *item);
    QVector<CustomToolsPluginInfo> mPluginList;
    CustomToolsPluginManager *const q;
};

void CustomToolsPluginManagerPrivate::initializePluginList()
{
    const QVector<KPluginMetaData> plugins = KPluginMetaData::findPlugins(QStringLiteral("pimcommon/customtools"));

    QVectorIterator<KPluginMetaData> i(plugins);
    i.toBack();
    QSet<QString> unique;
    while (i.hasPrevious()) {
        CustomToolsPluginInfo info;
        info.metaData = i.previous();
        if (info.metaData.version() == pluginVersion()) {
            // only load plugins once, even if found multiple times!
            if (unique.contains(info.saveName())) {
                continue;
            }
            info.plugin = nullptr;
            mPluginList.push_back(info);
            unique.insert(info.saveName());
        } else {
            qWarning() << "Plugin " << info.metaData.name() << " doesn't have correction plugin version. It will not be loaded.";
        }
    }
    QVector<CustomToolsPluginInfo>::iterator end(mPluginList.end());
    for (QVector<CustomToolsPluginInfo>::iterator it = mPluginList.begin(); it != end; ++it) {
        loadPlugin(&(*it));
    }
}

QVector<PimCommon::CustomToolsPlugin *> CustomToolsPluginManagerPrivate::pluginsList() const
{
    QVector<PimCommon::CustomToolsPlugin *> lst;
    QVector<CustomToolsPluginInfo>::ConstIterator end(mPluginList.constEnd());
    for (QVector<CustomToolsPluginInfo>::ConstIterator it = mPluginList.constBegin(); it != end; ++it) {
        if (auto plugin = (*it).plugin) {
            lst << plugin;
        }
    }
    return lst;
}

void CustomToolsPluginManagerPrivate::loadPlugin(CustomToolsPluginInfo *item)
{
    if (auto plugin = KPluginFactory::instantiatePlugin<PimCommon::CustomToolsPlugin>(item->metaData, q, QVariantList() << item->saveName()).plugin) {
        item->plugin = plugin;
    }
}

CustomToolsPluginManager *CustomToolsPluginManager::self()
{
    static CustomToolsPluginManager s_self;
    return &s_self;
}

CustomToolsPluginManager::CustomToolsPluginManager(QObject *parent)
    : QObject(parent)
    , d(new PimCommon::CustomToolsPluginManagerPrivate(this))
{
    d->initializePluginList();
}

CustomToolsPluginManager::~CustomToolsPluginManager() = default;

QVector<PimCommon::CustomToolsPlugin *> CustomToolsPluginManager::pluginsList() const
{
    return d->pluginsList();
}
