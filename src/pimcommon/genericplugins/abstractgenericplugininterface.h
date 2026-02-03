/*
  SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "pimcommon_export.h"
#include <QObject>
#include <memory>
class QAction;
class KActionCollection;
namespace PimCommon
{
class AbstractGenericPlugin;
class GenericPlugin;
/*!
 * \class ActionType
 * \brief The ActionType class provides type information for generic plugin actions
 * \inmodule PimCommon
 * \inheaderfile PimCommon/AbstractGenericPluginInterface
 * \author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT ActionType
{
public:
    enum Type {
        Tools = 0,
        Edit = 1,
        File = 2,
        Action = 3,
        PopupMenu = 4,
        ToolBar = 5,
        Message = 6,
        Folder = 7,
    };
    /*!
     * Constructs a default ActionType.
     */
    ActionType() = default;

    /*!
     * Constructs an ActionType with the given action and type.
     * @param action The QAction associated with this ActionType
     * @param type The type of action
     */
    ActionType(QAction *action, Type type);
    /*!
     * Returns the QAction associated with this ActionType.
     * @return The action, or nullptr if not set
     */
    [[nodiscard]] QAction *action() const;
    /*!
     * Returns the type of this action.
     * @return The action type
     */
    [[nodiscard]] Type type() const;

    /*!
     * Compares this ActionType with another for equality.
     * @param other The ActionType to compare with
     * @return true if both ActionTypes are equal, false otherwise
     */
    [[nodiscard]] bool operator==(ActionType other) const;

private:
    QAction *mAction = nullptr;
    Type mType = Tools;
};

class AbstractGenericPluginInterfacePrivate;
/*!
 * \class AbstractGenericPluginInterface
 * \brief The AbstractGenericPluginInterface class provides an interface for generic plugin implementations
 * \inmodule PimCommon
 * \inheaderfile PimCommon/AbstractGenericPluginInterface
 * \author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT AbstractGenericPluginInterface : public QObject
{
    Q_OBJECT
public:
    /*!
     * Constructs an AbstractGenericPluginInterface.
     * @param parent The parent QObject
     */
    explicit AbstractGenericPluginInterface(QObject *parent = nullptr);
    /*!
     * Destructs the AbstractGenericPluginInterface.
     */
    ~AbstractGenericPluginInterface() override;

    /*!
     * Sets the parent widget for this interface.
     * @param parent The widget to set as parent
     */
    void setParentWidget(QWidget *parent);
    /*!
     * Returns the parent widget of this interface.
     * @return The parent widget, or nullptr if not set
     */
    [[nodiscard]] QWidget *parentWidget() const;

    /*!
     * Sets the plugin for this interface.
     * @param plugin The AbstractGenericPlugin to set
     */
    void setPlugin(AbstractGenericPlugin *plugin);
    /*!
     * Returns the plugin associated with this interface.
     * @return The AbstractGenericPlugin, or nullptr if not set
     */
    [[nodiscard]] AbstractGenericPlugin *plugin() const;

    /*!
     * Creates actions for this plugin.
     * @param ac The KActionCollection to add actions to
     */
    virtual void createAction(KActionCollection *ac) = 0;
    /*!
     * Executes the plugin action.
     */
    virtual void exec() = 0;

    /*!
     * Shows the configuration dialog for this plugin.
     * @param parentWidget The parent widget for the dialog
     */
    virtual void showConfigureDialog(QWidget *parentWidget = nullptr);

Q_SIGNALS:
    /*!
     * Emitted when the plugin is activated.
     * @param interface Pointer to this interface
     */
    void emitPluginActivated(PimCommon::AbstractGenericPluginInterface *interface);
    /*!
     * Emitted to display a message.
     * @param str The message to display
     */
    void message(const QString &str);

private:
    std::unique_ptr<AbstractGenericPluginInterfacePrivate> const d;
};
}
