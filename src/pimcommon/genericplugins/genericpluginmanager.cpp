/*
  Copyright (c) 2015-2017 Montel Laurent <montel@kde.org>

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

#include "genericpluginmanager.h"
#include "genericplugin.h"
#include "pimcommon_debug.h"

#include <KPluginFactory>
#include <KPluginLoader>

#include <QFileInfo>

using namespace PimCommon;

class GenericPluginInfo
{
public:
    GenericPluginInfo()
        : plugin(nullptr)
        , isEnabled(true)
    {
    }

    QString metaDataFileNameBaseName;
    QString metaDataFileName;
    PimCommon::PluginUtilData pluginData;
    PimCommon::GenericPlugin *plugin = nullptr;
    bool isEnabled;
};

namespace {
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
    GenericPlugin *pluginFromIdentifier(const QString &id);
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
    const QVector<KPluginMetaData> plugins = KPluginLoader::findPlugins(pluginName, [this](const KPluginMetaData &md) {
        return md.serviceTypes().contains(serviceTypeName);
    });

    const QPair<QStringList, QStringList> pair = PimCommon::PluginUtil::loadPluginSetting(configGroupName(), configPrefixSettingKey());
    QVectorIterator<KPluginMetaData> i(plugins);
    i.toBack();
    QSet<QString> unique;
    while (i.hasPrevious()) {
        GenericPluginInfo info;
        const KPluginMetaData data = i.previous();

        //1) get plugin data => name/description etc.
        info.pluginData = PimCommon::PluginUtil::createPluginMetaData(data);
        //2) look at if plugin is activated
        const bool isPluginActivated = PimCommon::PluginUtil::isPluginActivated(pair.first, pair.second, info.pluginData.mEnableByDefault, info.pluginData.mIdentifier);
        info.isEnabled = isPluginActivated;
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
            qCWarning(PIMCOMMON_LOG) << "Plugin " << data.name() << " doesn't have correction plugin version. It will not be loaded.";
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
        if (auto plugin = (*it).plugin) {
            lst << plugin;
        }
    }
    return lst;
}

void GenericPluginManagerPrivate::loadPlugin(GenericPluginInfo *item)
{
    KPluginLoader pluginLoader(item->metaDataFileName);
    if (pluginLoader.factory()) {
        item->plugin = pluginLoader.factory()->create<PimCommon::GenericPlugin>(q, QVariantList() << item->metaDataFileNameBaseName);
        item->plugin->setIsEnabled(item->isEnabled);
        item->pluginData.mHasConfigureDialog = item->plugin->hasConfigureDialog();
        mPluginDataList.append(item->pluginData);
    }
}

GenericPlugin *GenericPluginManagerPrivate::pluginFromIdentifier(const QString &id)
{
    QVector<GenericPluginInfo>::ConstIterator end(mPluginList.constEnd());
    for (QVector<GenericPluginInfo>::ConstIterator it = mPluginList.constBegin(); it != end; ++it) {
        if ((*it).pluginData.mIdentifier == id) {
            return (*it).plugin;
        }
    }
    return {};
}

GenericPluginManager::GenericPluginManager(QObject *parent)
    : QObject(parent)
    , d(new GenericPluginManagerPrivate(this))
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

GenericPlugin *GenericPluginManager::pluginFromIdentifier(const QString &id)
{
    return d->pluginFromIdentifier(id);
}
