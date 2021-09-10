/*
   SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "addressesslineeditpluginmanager.h"
#include "addressesslineeditabstractplugin.h"
#include "kcoreaddons_version.h"
#include "pimcommonakonadi_debug.h"
#include <KPluginFactory>
#include <KPluginLoader>
#include <KPluginMetaData>

#include <QFileInfo>

using namespace PimCommon;

class AddressessLineEditPluginInfo
{
public:
    AddressessLineEditPluginInfo()
    {
    }

    KPluginMetaData data;
    QString metaDataFileNameBaseName;
    QString metaDataFileName;
    PimCommon::AddressessLineEditAbstractPlugin *plugin = nullptr;
};

namespace
{
QString pluginVersion()
{
    return QStringLiteral("1.0");
}
}

class PimCommon::AddressessLineEditPluginManagerPrivate
{
public:
    AddressessLineEditPluginManagerPrivate(AddressessLineEditPluginManager *qq)
        : q(qq)
    {
        initializePlugins();
    }

    void loadPlugin(AddressessLineEditPluginInfo *item);
    QVector<PimCommon::AddressessLineEditAbstractPlugin *> pluginsList() const;
    QVector<AddressessLineEditPluginInfo> mPluginList;
    bool initializePlugins();

private:
    AddressessLineEditPluginManager *const q;
};

bool AddressessLineEditPluginManagerPrivate::initializePlugins()
{
    if (!mPluginList.isEmpty()) {
        return true;
    }
#if KCOREADDONS_VERSION < QT_VERSION_CHECK(5, 86, 0)
    const QVector<KPluginMetaData> plugins = KPluginLoader::findPlugins(QStringLiteral("addressline"));
#else
    const QVector<KPluginMetaData> plugins = KPluginMetaData::findPlugins(QStringLiteral("addressline"));
#endif

    QVectorIterator<KPluginMetaData> i(plugins);
    i.toBack();
    while (i.hasPrevious()) {
        AddressessLineEditPluginInfo info;
        const KPluginMetaData data = i.previous();

        info.metaDataFileNameBaseName = QFileInfo(data.fileName()).baseName();
        info.metaDataFileName = data.fileName();
        info.data = data;
        if (pluginVersion() == data.version()) {
            info.plugin = nullptr;
            mPluginList.push_back(info);
        } else {
            qCWarning(PIMCOMMONAKONADI_LOG) << "Plugin " << data.name() << " doesn't have correction plugin version. It will not be loaded.";
        }
    }
    const QVector<AddressessLineEditPluginInfo>::iterator end(mPluginList.end());
    for (QVector<AddressessLineEditPluginInfo>::iterator it = mPluginList.begin(); it != end; ++it) {
        loadPlugin(&(*it));
    }
    return true;
}

void AddressessLineEditPluginManagerPrivate::loadPlugin(AddressessLineEditPluginInfo *item)
{
#if KCOREADDONS_VERSION < QT_VERSION_CHECK(5, 86, 0)
    KPluginLoader pluginLoader(item->metaDataFileName);
    if (pluginLoader.factory()) {
        item->plugin = pluginLoader.factory()->create<PimCommon::AddressessLineEditAbstractPlugin>(q, QVariantList() << item->metaDataFileNameBaseName);
    }
#else
    if (auto plugin =
            KPluginFactory::instantiatePlugin<PimCommon::AddressessLineEditAbstractPlugin>(item->data, q, QVariantList() << item->metaDataFileNameBaseName)
                .plugin) {
        item->plugin = plugin;
    }
#endif
}

QVector<PimCommon::AddressessLineEditAbstractPlugin *> AddressessLineEditPluginManagerPrivate::pluginsList() const
{
    QVector<PimCommon::AddressessLineEditAbstractPlugin *> lst;
    const QVector<AddressessLineEditPluginInfo>::ConstIterator end(mPluginList.constEnd());
    for (QVector<AddressessLineEditPluginInfo>::ConstIterator it = mPluginList.constBegin(); it != end; ++it) {
        if (auto plugin = (*it).plugin) {
            lst << plugin;
        }
    }
    return lst;
}

AddressessLineEditPluginManager::AddressessLineEditPluginManager(QObject *parent)
    : QObject(parent)
    , d(new AddressessLineEditPluginManagerPrivate(this))
{
}

AddressessLineEditPluginManager::~AddressessLineEditPluginManager()
{
    delete d;
}

AddressessLineEditPluginManager *AddressessLineEditPluginManager::self()
{
    static AddressessLineEditPluginManager s_self;
    return &s_self;
}

QVector<PimCommon::AddressessLineEditAbstractPlugin *> AddressessLineEditPluginManager::pluginsList() const
{
    return d->pluginsList();
}

PimCommon::AddressessLineEditAbstractPlugin *AddressessLineEditPluginManager::plugin(const QString &identifier)
{
    const QVector<PimCommon::AddressessLineEditAbstractPlugin *> lstPlugins = pluginsList();
    for (PimCommon::AddressessLineEditAbstractPlugin *p : lstPlugins) {
        const QVector<AddressessLineEditAbstractPluginInfo> lstPluginsInfo = p->names();
        for (const AddressessLineEditAbstractPluginInfo &info : lstPluginsInfo) {
            if (info.identifier == identifier) {
                return p;
            }
        }
    }
    return {};
}
