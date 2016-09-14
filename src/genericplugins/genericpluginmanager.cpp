/*
  Copyright (c) 2015-2016 Montel Laurent <montel@kde.org>

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

#include "genericplugin.h"
#include "genericpluginmanager.h"
#include "pimcommon_debug.h"
#include "pluginutil.h"

#include <kpluginmetadata.h>
#include <KPluginLoader>
#include <KPluginFactory>
#include <KSharedConfig>
#include <KConfigGroup>
#include <qfileinfo.h>
#include <QVariant>
#include <QSet>
#include <QVariantList>
#include <QDebug>

using namespace PimCommon;

class GenericPluginManagerInstancePrivate
{
public:
    GenericPluginManagerInstancePrivate()
        : genericPluginManager(new GenericPluginManager)
    {
    }

    ~GenericPluginManagerInstancePrivate()
    {
        delete genericPluginManager;
    }

    GenericPluginManager *genericPluginManager;
};

Q_GLOBAL_STATIC(GenericPluginManagerInstancePrivate, sInstance)

class GenericPluginInfo
{
public:
    GenericPluginInfo()
        : plugin(Q_NULLPTR)
    {

    }
    QString saveName() const;

    KPluginMetaData metaData;
    PimCommon::GenericPlugin *plugin;
};

QString GenericPluginInfo::saveName() const
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

class PimCommon::GenericPluginManagerPrivate
{
public:
    GenericPluginManagerPrivate(GenericPluginManager *qq)
        : q(qq)
    {

    }
    void loadPlugin(GenericPluginInfo *item);
    QVector<GenericPlugin *> pluginsList() const;
    bool initializePlugins();
    QString serviceTypeName;
    QString pluginName;
    QVector<GenericPluginInfo> mPluginList;

    QVector<PluginUtilData> pluginsDataList() const;
    QString configGroupName() const;
    QString configPrefixSettingKey() const;
private:
    QVector<PluginUtilData> mPluginDataList;
    GenericPluginManager *q;
};

QString GenericPluginManagerPrivate::configGroupName() const
{
    return QStringLiteral("GenericPlugin-%1").arg(pluginName);
}

QString GenericPluginManagerPrivate::configPrefixSettingKey() const
{
    return QStringLiteral("%1Plugin").arg(pluginName);
}

bool GenericPluginManagerPrivate::initializePlugins()
{
    if (!mPluginList.isEmpty()) {
        return true;
    }

    if (serviceTypeName.isEmpty() || pluginName.isEmpty()) {
        return false;
    }
    static const QString s_serviceTypeName = serviceTypeName;
    const QVector<KPluginMetaData> plugins = KPluginLoader::findPlugins(pluginName, [](const KPluginMetaData & md) {
        return md.serviceTypes().contains(s_serviceTypeName);
    });

    const QPair<QStringList, QStringList> pair = PimCommon::PluginUtil::loadPluginSetting(configGroupName(), configPrefixSettingKey());
    QVectorIterator<KPluginMetaData> i(plugins);
    i.toBack();
    QSet<QString> unique;
    while (i.hasPrevious()) {
        GenericPluginInfo info;
        info.metaData = i.previous();

        const PimCommon::PluginUtilData pluginData = PimCommon::PluginUtil::createPluginMetaData(info.metaData);
        mPluginDataList.append(pluginData);

        const bool isPluginActivated = PimCommon::PluginUtil::isPluginActivated(pair.first, pair.second, pluginData.mEnableByDefault, pluginData.mIdentifier);
        if (isPluginActivated) {
            if (pluginVersion() == info.metaData.version()) {
                // only load plugins once, even if found multiple times!
                if (unique.contains(info.saveName())) {
                    continue;
                }
                info.plugin = Q_NULLPTR;
                mPluginList.push_back(info);
                unique.insert(info.saveName());
            } else {
                qCWarning(PIMCOMMON_LOG) << "Plugin " << info.metaData.name() << " doesn't have correction plugin version. It will not be loaded.";
            }
        }
    }
    QVector<GenericPluginInfo>::iterator end(mPluginList.end());
    for (QVector<GenericPluginInfo>::iterator it = mPluginList.begin(); it != end; ++it) {
        loadPlugin(&(*it));
    }
    return true;
}

QVector<PluginUtilData> GenericPluginManagerPrivate::pluginsDataList() const
{
    return mPluginDataList;
}

QVector<GenericPlugin *> GenericPluginManagerPrivate::pluginsList() const
{
    QVector<PimCommon::GenericPlugin *> lst;
    QVector<GenericPluginInfo>::ConstIterator end(mPluginList.constEnd());
    for (QVector<GenericPluginInfo>::ConstIterator it = mPluginList.constBegin(); it != end; ++it) {
        if ((*it).plugin) {
            lst << (*it).plugin;
        }
    }
    return lst;
}

void GenericPluginManagerPrivate::loadPlugin(GenericPluginInfo *item)
{
    KPluginLoader pluginLoader(item->metaData.fileName());
    if (pluginLoader.factory()) {
        item->plugin = pluginLoader.factory()->create<PimCommon::GenericPlugin>(q, QVariantList() << item->saveName());
    }
}

GenericPluginManager::GenericPluginManager(QObject *parent)
    : QObject(parent),
      d(new GenericPluginManagerPrivate(this))
{

}

GenericPluginManager::~GenericPluginManager()
{
    delete d;
}

bool GenericPluginManager::initializePlugins()
{
    return d->initializePlugins();
}

void GenericPluginManager::setServiceTypeName(const QString &serviceName)
{
    d->serviceTypeName = serviceName;
}

QString GenericPluginManager::serviceTypeName() const
{
    return d->serviceTypeName;
}

void GenericPluginManager::setPluginName(const QString &pluginName)
{
    d->pluginName = pluginName;
}

QString GenericPluginManager::pluginName() const
{
    return d->pluginName;
}

GenericPluginManager *GenericPluginManager::self()
{
    return sInstance->genericPluginManager;
}

QVector<GenericPlugin *> GenericPluginManager::pluginsList() const
{
    return d->pluginsList();
}

QVector<PluginUtilData> GenericPluginManager::pluginsDataList() const
{
    return d->pluginsDataList();
}

QString GenericPluginManager::configGroupName() const
{
    return d->configGroupName();
}

QString GenericPluginManager::configPrefixSettingKey() const
{
    return d->configPrefixSettingKey();
}
