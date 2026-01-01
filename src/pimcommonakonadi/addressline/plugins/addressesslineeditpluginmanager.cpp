/*
   SPDX-FileCopyrightText: 2017-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "addressesslineeditpluginmanager.h"
#include "addressesslineeditabstractplugin.h"
#include "pimcommonakonadi_debug.h"
#include <KPluginFactory>
#include <KPluginMetaData>

#include <QFileInfo>

using namespace PimCommon;

class AddressessLineEditPluginInfo
{
public:
    AddressessLineEditPluginInfo() = default;

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
    explicit AddressessLineEditPluginManagerPrivate(AddressessLineEditPluginManager *qq)
        : q(qq)
    {
        initializePlugins();
    }

    void loadPlugin(AddressessLineEditPluginInfo *item);
    [[nodiscard]] QList<PimCommon::AddressessLineEditAbstractPlugin *> pluginsList() const;
    QList<AddressessLineEditPluginInfo> mPluginList;
    bool initializePlugins();

private:
    AddressessLineEditPluginManager *const q;
};

bool AddressessLineEditPluginManagerPrivate::initializePlugins()
{
    if (!mPluginList.isEmpty()) {
        return true;
    }
    const QList<KPluginMetaData> plugins = KPluginMetaData::findPlugins(QStringLiteral("addressline"));
    QListIterator<KPluginMetaData> i(plugins);
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
    const QList<AddressessLineEditPluginInfo>::iterator end(mPluginList.end());
    for (QList<AddressessLineEditPluginInfo>::iterator it = mPluginList.begin(); it != end; ++it) {
        loadPlugin(&(*it));
    }
    return true;
}

void AddressessLineEditPluginManagerPrivate::loadPlugin(AddressessLineEditPluginInfo *item)
{
    if (auto plugin =
            KPluginFactory::instantiatePlugin<PimCommon::AddressessLineEditAbstractPlugin>(item->data, q, QVariantList() << item->metaDataFileNameBaseName)
                .plugin) {
        item->plugin = plugin;
    }
}

QList<PimCommon::AddressessLineEditAbstractPlugin *> AddressessLineEditPluginManagerPrivate::pluginsList() const
{
    QList<PimCommon::AddressessLineEditAbstractPlugin *> lst;
    const QList<AddressessLineEditPluginInfo>::ConstIterator end(mPluginList.constEnd());
    for (QList<AddressessLineEditPluginInfo>::ConstIterator it = mPluginList.constBegin(); it != end; ++it) {
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

AddressessLineEditPluginManager::~AddressessLineEditPluginManager() = default;

AddressessLineEditPluginManager *AddressessLineEditPluginManager::self()
{
    static AddressessLineEditPluginManager s_self;
    return &s_self;
}

QList<PimCommon::AddressessLineEditAbstractPlugin *> AddressessLineEditPluginManager::pluginsList() const
{
    return d->pluginsList();
}

PimCommon::AddressessLineEditAbstractPlugin *AddressessLineEditPluginManager::plugin(const QString &identifier)
{
    const QList<PimCommon::AddressessLineEditAbstractPlugin *> lstPlugins = pluginsList();
    for (PimCommon::AddressessLineEditAbstractPlugin *p : lstPlugins) {
        const QList<AddressessLineEditAbstractPluginInfo> lstPluginsInfo = p->names();
        for (const AddressessLineEditAbstractPluginInfo &info : lstPluginsInfo) {
            if (info.identifier == identifier) {
                return p;
            }
        }
    }
    return {};
}

#include "moc_addressesslineeditpluginmanager.cpp"
