/*
  SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "customtoolspluginmanager.h"
#include "customtoolsplugin.h"
#include "kcoreaddons_version.h"

#include <KPluginFactory>
#include <KPluginLoader>
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

    QVector<PimCommon::CustomToolsPlugin *> pluginsList() const;
    void initializePluginList();
    void loadPlugin(CustomToolsPluginInfo *item);
    QVector<CustomToolsPluginInfo> mPluginList;
    CustomToolsPluginManager *const q;
};

void CustomToolsPluginManagerPrivate::initializePluginList()
{
#if KCOREADDONS_VERSION < QT_VERSION_CHECK(5, 86, 0)
    const QVector<KPluginMetaData> plugins = KPluginLoader::findPlugins(QStringLiteral("pimcommon/customtools"));
#else
    const QVector<KPluginMetaData> plugins = KPluginMetaData::findPlugins(QStringLiteral("pimcommon/customtools"));
#endif

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
#if KCOREADDONS_VERSION < QT_VERSION_CHECK(5, 85, 0)
    KPluginLoader pluginLoader(item->metaData.fileName());
    if (pluginLoader.factory()) {
        item->plugin = pluginLoader.factory()->create<PimCommon::CustomToolsPlugin>(q, QVariantList() << item->saveName());
    }
#else
    if (auto plugin = KPluginFactory::instantiatePlugin<PimCommon::CustomToolsPlugin>(item->metaData, q, QVariantList() << item->saveName()).plugin) {
        item->plugin = plugin;
    }
#endif
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

CustomToolsPluginManager::~CustomToolsPluginManager()
{
    delete d;
}

QVector<PimCommon::CustomToolsPlugin *> CustomToolsPluginManager::pluginsList() const
{
    return d->pluginsList();
}
