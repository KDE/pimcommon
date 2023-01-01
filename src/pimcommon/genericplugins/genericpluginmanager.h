/*
  SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "pimcommon_export.h"
#include <PimCommon/PluginUtil>
#include <QObject>
#include <QVector>

namespace PimCommon
{
class GenericPluginManagerPrivate;
class GenericPlugin;
/**
 * @brief The GenericPluginManager class
 * @author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT GenericPluginManager : public QObject
{
    Q_OBJECT
public:
    class GenericPluginData
    {
    public:
        GenericPluginData() = default;

        QString mDescription;
        QString mName;
        QString mIdentifier;
        bool mEnableByDefault = false;
    };

    explicit GenericPluginManager(QObject *parent = nullptr);
    ~GenericPluginManager() override;

    Q_REQUIRED_RESULT bool initializePlugins();

    void setPluginDirectory(const QString &directory);
    Q_REQUIRED_RESULT QString pluginDirectory() const;

    void setPluginName(const QString &pluginName);
    Q_REQUIRED_RESULT QString pluginName() const;

    Q_REQUIRED_RESULT QVector<PimCommon::GenericPlugin *> pluginsList() const;
    Q_REQUIRED_RESULT QVector<PimCommon::PluginUtilData> pluginsDataList() const;

    Q_REQUIRED_RESULT QString configGroupName() const;
    Q_REQUIRED_RESULT QString configPrefixSettingKey() const;

    Q_REQUIRED_RESULT GenericPlugin *pluginFromIdentifier(const QString &id);

private:
    std::unique_ptr<GenericPluginManagerPrivate> const d;
};
}
