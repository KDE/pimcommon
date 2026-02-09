/*
  SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "pimcommon_export.h"
#include <QWidget>
class KToggleAction;
class KActionCollection;
namespace PimCommon
{
class CustomToolsWidgetNgPrivate;
class CustomToolsPlugin;
class CustomToolsViewInterface;
/*!
 * \class PimCommon::CustomToolsWidgetNg
 * \brief The CustomToolsWidgetNg class provides a widget for custom tools
 * \inmodule PimCommon
 * \inheaderfile PimCommon/CustomToolsWidgetNg
 * \author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT CustomToolsWidgetNg : public QWidget
{
    Q_OBJECT
public:
    /*!
     * Constructs a CustomToolsWidgetNg.
     * @param parent The parent widget
     */
    explicit CustomToolsWidgetNg(QWidget *parent = nullptr);
    /*!
     * Destructs the CustomToolsWidgetNg.
     */
    ~CustomToolsWidgetNg() override;

    /*!
     * Returns the list of actions for toggling custom tool views.
     * @return A list of KToggleAction for custom tools
     */
    [[nodiscard]] QList<KToggleAction *> actionList() const;
    /*!
     * Initializes the view with the given action collection and plugins.
     * @param ac The KActionCollection to add actions to
     * @param localPluginsList The list of CustomToolsPlugin instances
     */
    void initializeView(KActionCollection *ac, const QList<CustomToolsPlugin *> &localPluginsList);

    /*!
     * Sets the text for the custom tools.
     * @param text The text to display
     */
    void setText(const QString &text);

    /*!
     * Adds a custom tools view interface.
     * @param plugin The CustomToolsViewInterface to add
     */
    void addCustomToolViewInterface(PimCommon::CustomToolsViewInterface *plugin);

public Q_SLOTS:
    /*!
     * Called when a tool is closed.
     */
    void slotToolsWasClosed();
    /*!
     * Called to activate a view.
     * @param w The widget to activate
     */
    void slotActivateView(QWidget *w);

Q_SIGNALS:
    /*!
     * Emitted when text should be inserted.
     * @param url The text/URL to insert
     */
    void insertText(const QString &url);
    /*!
     * Emitted when a tool is activated.
     */
    void toolActivated();

private:
    std::unique_ptr<CustomToolsWidgetNgPrivate> const d;
};
}
