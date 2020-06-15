/*
   Copyright (C) 2017-2020 Laurent Montel <montel@kde.org>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "addressesslineeditpluginmanager.h"
#include "addressesslineeditabstractplugin.h"
#include "pimcommonakonadi_debug.h"

#include <KPluginMetaData>
#include <KPluginLoader>
#include <KPluginFactory>

#include <QFileInfo>
#include <QSet>

using namespace PimCommon;

class AddressessLineEditPluginInfo
{
public:
    AddressessLineEditPluginInfo()
    {
    }

    QString metaDataFileNameBaseName;
    QString metaDataFileName;
    PimCommon::AddressessLineEditAbstractPlugin *plugin = nullptr;
};

namespace {
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
    AddressessLineEditPluginManager *q;
};

bool AddressessLineEditPluginManagerPrivate::initializePlugins()
{
    if (!mPluginList.isEmpty()) {
        return true;
    }
    const QVector<KPluginMetaData> plugins = KPluginLoader::findPlugins(QStringLiteral("addressline"));

    QVectorIterator<KPluginMetaData> i(plugins);
    i.toBack();
    QSet<QString> unique;
    while (i.hasPrevious()) {
        AddressessLineEditPluginInfo info;
        const KPluginMetaData data = i.previous();

        info.metaDataFileNameBaseName = QFileInfo(data.fileName()).baseName();
        info.metaDataFileName = data.fileName();
        if (pluginVersion() == data.version()) {
            // only load plugins once, even if found multiple times!
            if (unique.contains(info.metaDataFileNameBaseName)) {
                continue;
            }
            info.plugin = nullptr;
            mPluginList.push_back(info);
            unique.insert(info.metaDataFileNameBaseName);
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
    KPluginLoader pluginLoader(item->metaDataFileName);
    if (pluginLoader.factory()) {
        item->plugin = pluginLoader.factory()->create<PimCommon::AddressessLineEditAbstractPlugin>(q, QVariantList() << item->metaDataFileNameBaseName);
    }
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
