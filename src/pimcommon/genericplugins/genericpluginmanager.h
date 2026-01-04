/*
  SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "pimcommon_export.h"
#include <PimCommon/PluginUtil>
#include <QList>
#include <QObject>
#include <TextAddonsWidgets/PluginUtil>

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
    /*!
     */
    class GenericPluginData
    {
    public:
        GenericPluginData() = default;

        QString mDescription;
        QString mName;
        QString mIdentifier;
        bool mEnableByDefault = false;
    };

    /*!
     */
    explicit GenericPluginManager(QObject *parent = nullptr);
    /*!
     */
    ~GenericPluginManager() override;

    /*!
     */
    [[nodiscard]] bool initializePlugins();

    /*!
     */
    void setPluginDirectory(const QString &directory);
    /*!
     */
    [[nodiscard]] QString pluginDirectory() const;

    /*!
     */
    void setPluginName(const QString &pluginName);
    /*!
     */
    [[nodiscard]] QString pluginName() const;

    /*!
     */
    [[nodiscard]] QList<PimCommon::GenericPlugin *> pluginsList() const;
    /*!
     */
    [[nodiscard]] QList<TextAddonsWidgets::PluginUtilData> pluginsDataList() const;

    /*!
     */
    [[nodiscard]] QString configGroupName() const;
    /*!
     */
    [[nodiscard]] QString configPrefixSettingKey() const;

    /*!
     */
    [[nodiscard]] GenericPlugin *pluginFromIdentifier(const QString &id);

private:
    std::unique_ptr<GenericPluginManagerPrivate> const d;
};
}
