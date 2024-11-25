/*
  SPDX-FileCopyrightText: 2016-2024 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "pimcommon_export.h"
#include <QWidget>
class KMessageWidget;
namespace PimCommon
{
class ConfigurePluginsListWidget;
/**
 * @brief The ConfigurePluginsWidget class
 * @author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT ConfigurePluginsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ConfigurePluginsWidget(QWidget *parent = nullptr);
    explicit ConfigurePluginsWidget(ConfigurePluginsListWidget *configurePluginListWidget, QWidget *parent = nullptr);
    ~ConfigurePluginsWidget() override;

    void save();
    void defaults();
    void doLoadFromGlobalSettings();
    void doResetToDefaultsOther();

Q_SIGNALS:
    void wasChanged(bool changed);

private:
    PIMCOMMON_NO_EXPORT void initialize();
    PIMCOMMON_NO_EXPORT void slotConfigChanged();
    PIMCOMMON_NO_EXPORT void initLayout(ConfigurePluginsListWidget *configurePluginListWidget = nullptr);

    ConfigurePluginsListWidget *mConfigureListWidget = nullptr;
    KMessageWidget *mMessageWidget = nullptr;
};
}
