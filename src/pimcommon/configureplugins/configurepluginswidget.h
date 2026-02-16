/*
  SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "pimcommon_export.h"
#include <QWidget>
#include <TextAddonsWidgets/ConfigurePluginsWidget>
class KMessageWidget;
namespace PimCommon
{
/*!
 * \class PimCommon::ConfigurePluginsWidget
 * \brief The ConfigurePluginsWidget class provides a widget for configuring plugins
 * \inmodule PimCommon
 * \inheaderfile PimCommon/ConfigurePluginsWidget
 * \author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT ConfigurePluginsWidget : public QWidget
{
    Q_OBJECT
public:
    /*!
     * Constructs a ConfigurePluginsWidget.
     * @param parent The parent widget
     */
    explicit ConfigurePluginsWidget(QWidget *parent = nullptr);
    /*!
     * Constructs a ConfigurePluginsWidget with a custom plugin configuration widget.
     * @param configurePluginListWidget The custom ConfigurePluginsWidget to use
     * @param parent The parent widget
     */
    explicit ConfigurePluginsWidget(TextAddonsWidgets::ConfigurePluginsWidget *configurePluginListWidget, QWidget *parent = nullptr);
    /*!
     * Destructs the ConfigurePluginsWidget.
     */
    ~ConfigurePluginsWidget() override;

    /*!
     * Saves the configuration of all plugins.
     */
    void save();
    /*!
     * Resets the configuration to default values.
     */
    void defaults();
    /*!
     * Loads the global settings for the plugins.
     */
    void doLoadFromGlobalSettings();
    /*!
     * Resets to default values other than configuration.
     */
    void doResetToDefaultsOther();

Q_SIGNALS:
    /*!
     * Emitted when the configuration changes.
     * @param changed true if the configuration has changed
     */
    void wasChanged(bool changed);

private:
    PIMCOMMON_NO_EXPORT void initialize();
    PIMCOMMON_NO_EXPORT void slotConfigChanged();
    PIMCOMMON_NO_EXPORT void initLayout(TextAddonsWidgets::ConfigurePluginsWidget *configurePluginListWidget = nullptr);

    TextAddonsWidgets::ConfigurePluginsWidget *mConfigureListWidget = nullptr;
};
}
