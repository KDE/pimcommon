/*
  SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "genericpluginmanager.h"
#include "genericplugin.h"
#include "pimcommon_debug.h"

#include <KPluginFactory>

#include <QFileInfo>

using namespace PimCommon;

class GenericPluginInfo
{
public:
    GenericPluginInfo() = default;

    KPluginMetaData data;
    QString metaDataFileNameBaseName;
    QString metaDataFileName;
    PimCommon::PluginUtilData pluginData;
    PimCommon::GenericPlugin *plugin = nullptr;
    bool isEnabled = true;
};

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
    explicit GenericPluginManagerPrivate(GenericPluginManager *qq)
        : q(qq)
    {
    }

    void loadPlugin(GenericPluginInfo *item);
    Q_REQUIRED_RESULT QVector<GenericPlugin *> pluginsList() const;
    bool initializePlugins();
    QString pluginDirectory;
    QString pluginName;
    QVector<GenericPluginInfo> mPluginList;

    Q_REQUIRED_RESULT QVector<PluginUtilData> pluginsDataList() const;
    Q_REQUIRED_RESULT QString configGroupName() const;
    Q_REQUIRED_RESULT QString configPrefixSettingKey() const;
    GenericPlugin *pluginFromIdentifier(const QString &id);

private:
    QVector<PluginUtilData> mPluginDataList;
    GenericPluginManager *const q;
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

    if (pluginDirectory.isEmpty() || pluginName.isEmpty()) {
        return false;
    }
    const QVector<KPluginMetaData> plugins = KPluginMetaData::findPlugins(pluginDirectory);

    const QPair<QStringList, QStringList> pair = PimCommon::PluginUtil::loadPluginSetting(configGroupName(), configPrefixSettingKey());
    QVectorIterator<KPluginMetaData> i(plugins);
    i.toBack();
    while (i.hasPrevious()) {
        GenericPluginInfo info;
        const KPluginMetaData data = i.previous();

        // 1) get plugin data => name/description etc.
        info.pluginData = PimCommon::PluginUtil::createPluginMetaData(data);
        // 2) look at if plugin is activated
        const bool isPluginActivated =
            PimCommon::PluginUtil::isPluginActivated(pair.first, pair.second, info.pluginData.mEnableByDefault, info.pluginData.mIdentifier);
        info.isEnabled = isPluginActivated;
        info.metaDataFileNameBaseName = QFileInfo(data.fileName()).baseName();
        info.metaDataFileName = data.fileName();
        info.data = data;

        if (pluginVersion() == data.version()) {
            info.plugin = nullptr;
            mPluginList.push_back(info);
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
    if (auto plugin = KPluginFactory::instantiatePlugin<PimCommon::GenericPlugin>(item->data, q, QVariantList() << item->metaDataFileNameBaseName).plugin) {
        item->plugin = plugin;
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

GenericPluginManager::~GenericPluginManager() = default;

bool GenericPluginManager::initializePlugins()
{
    return d->initializePlugins();
}

void GenericPluginManager::setPluginDirectory(const QString &directory)
{
    d->pluginDirectory = directory;
}

QString GenericPluginManager::pluginDirectory() const
{
    return d->pluginDirectory;
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
