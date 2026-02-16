/*
  SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "pimcommon_export.h"
#include <QObject>
#include <memory>
class KActionCollection;
namespace PimCommon
{
class CustomToolsWidgetNg;
class CustomToolsViewInterface;
class CustomToolsPluginPrivate;
/*!
 * \class PimCommon::CustomToolsPlugin
 * \brief The CustomToolsPlugin class provides the base class for custom tools plugins
 * \inmodule PimCommon
 * \inheaderfile PimCommon/CustomToolsPlugin
 * \author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT CustomToolsPlugin : public QObject
{
    Q_OBJECT
public:
    /*!
     * Constructs a CustomToolsPlugin.
     * @param parent The parent QObject
     */
    explicit CustomToolsPlugin(QObject *parent = nullptr);
    /*!
     * Destructs the CustomToolsPlugin.
     */
    ~CustomToolsPlugin() override;

    /*!
     * Creates a view interface for this custom tool.
     * @param ac The KActionCollection to add actions to
     * @param parent The parent CustomToolsWidgetNg
     * @return A new CustomToolsViewInterface instance
     */
    virtual PimCommon::CustomToolsViewInterface *createView(KActionCollection *ac, CustomToolsWidgetNg *parent = nullptr) = 0;
    /*!
     * Returns the name of the custom tool.
     * @return The custom tool name
     */
    [[nodiscard]] virtual QString customToolName() const = 0;

    /*!
     * Returns whether this plugin has a configuration dialog.
     * @return true if configuration dialog is available, false otherwise
     */
    [[nodiscard]] virtual bool hasConfigureDialog() const;
    /*!
     * Shows the configuration dialog for this plugin.
     * @param parent The parent widget
     */
    virtual void showConfigureDialog(QWidget *parent);

    /*!
     * Emits the configuration changed signal.
     */
    void emitConfigChanged();

    /*!
     * Returns the description of this custom tool.
     * @return The tool description
     */
    [[nodiscard]] virtual QString description() const;

    /*!
     * Sets whether this plugin is enabled.
     * @param enabled true to enable, false to disable
     */
    void setIsEnabled(bool enabled);
    /*!
     * Returns whether this plugin is enabled.
     * @return true if enabled, false otherwise
     */
    [[nodiscard]] bool isEnabled() const;

private:
    std::unique_ptr<CustomToolsPluginPrivate> const d;
};
}
