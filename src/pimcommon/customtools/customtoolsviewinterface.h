/*
  SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "pimcommon_export.h"

#include <QWidget>
class KToggleAction;
namespace PimCommon
{
/*!
 * \class CustomToolsViewInterface
 * \brief The CustomToolsViewInterface class provides the interface for custom tools views
 * \inmodule PimCommon
 * \inheaderfile PimCommon/CustomToolsViewInterface
 * \author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT CustomToolsViewInterface : public QWidget
{
    Q_OBJECT
public:
    /*!
     * Constructs a CustomToolsViewInterface.
     * @param parent The parent widget
     */
    explicit CustomToolsViewInterface(QWidget *parent = nullptr);
    /*!
     * Destructs the CustomToolsViewInterface.
     */
    ~CustomToolsViewInterface() override;

    /*!
     * Sets the text displayed in the view.
     * @param text The text to display
     */
    virtual void setText(const QString &text);
    /*!
     * Returns the action associated with this view.
     * @return A KToggleAction for toggling this view
     */
    [[nodiscard]] virtual KToggleAction *action() const;

Q_SIGNALS:
    /*!
     * Emitted when text should be inserted.
     * @param text The text to insert
     */
    void insertText(const QString &text);
    /*!
     * Emitted when the tools view is closed.
     */
    void toolsWasClosed();
    /*!
     * Emitted to activate the view.
     * @param widget The widget to activate
     */
    void activateView(QWidget *);
    /*!
     * Emitted to configure the tools.
     * @param parent The parent widget for configuration dialog
     */
    void configure(QWidget *parent);
};
}
