/*
  SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "pimcommon_export.h"
#include <QObject>
namespace PimCommon
{
class AbstractGenericPluginInterface;
/*!
 * \class AbstractGenericPlugin
 * \brief The AbstractGenericPlugin class provides the base class for generic plugins
 * \inmodule PimCommon
 * \inheaderfile PimCommon/AbstractGenericPlugin
 * \author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT AbstractGenericPlugin : public QObject
{
    Q_OBJECT
public:
    /*!
     * Constructs an AbstractGenericPlugin.
     * @param parent The parent QObject
     */
    explicit AbstractGenericPlugin(QObject *parent = nullptr);
    /*!
     * Destructs the AbstractGenericPlugin.
     */
    ~AbstractGenericPlugin() override;

    /*!
     * Creates an interface for this plugin.
     * @param parent The parent QObject
     * @return A new AbstractGenericPluginInterface instance
     */
    virtual PimCommon::AbstractGenericPluginInterface *createInterface(QObject *parent = nullptr) = 0;
    /*!
     * Returns whether this plugin has popup menu support.
     * @return true if popup menu is supported, false otherwise
     */
    [[nodiscard]] virtual bool hasPopupMenuSupport() const;
    /*!
     * Returns whether this plugin has toolbar support.
     * @return true if toolbar is supported, false otherwise
     */
    [[nodiscard]] virtual bool hasToolBarSupport() const;
    /*!
     * Returns whether this plugin has a configuration dialog.
     * @return true if configuration dialog is available, false otherwise
     */
    [[nodiscard]] virtual bool hasConfigureDialog() const;
    /*!
     * Returns whether this plugin has status bar support.
     * @return true if status bar is supported, false otherwise
     */
    [[nodiscard]] virtual bool hasStatusBarSupport() const;

    /*!
     */
    /*!
     * Shows the configuration dialog for this plugin.
     * @param parent The parent widget
     */
    virtual void showConfigureDialog(QWidget *parent = nullptr);

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

Q_SIGNALS:
    /*!
     * Emitted when the plugin configuration changes.
     */
    void configChanged();

private:
    bool mIsEnabled = true;
};
}
