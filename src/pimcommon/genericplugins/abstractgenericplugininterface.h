/*
  SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

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
/**
 * @brief The ActionType class
 * @author Laurent Montel <montel@kde.org>
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
    ActionType() = default;

    ActionType(QAction *action, Type type);
    [[nodiscard]] QAction *action() const;
    [[nodiscard]] Type type() const;

    [[nodiscard]] bool operator==(ActionType other) const;

private:
    QAction *mAction = nullptr;
    Type mType = Tools;
};

class AbstractGenericPluginInterfacePrivate;
class PIMCOMMON_EXPORT AbstractGenericPluginInterface : public QObject
{
    Q_OBJECT
public:
    explicit AbstractGenericPluginInterface(QObject *parent = nullptr);
    ~AbstractGenericPluginInterface() override;

    void setParentWidget(QWidget *parent);
    [[nodiscard]] QWidget *parentWidget() const;

    void setPlugin(AbstractGenericPlugin *plugin);
    [[nodiscard]] AbstractGenericPlugin *plugin() const;

    virtual void createAction(KActionCollection *ac) = 0;
    virtual void exec() = 0;

    virtual void showConfigureDialog(QWidget *parentWidget = nullptr);

Q_SIGNALS:
    void emitPluginActivated(PimCommon::AbstractGenericPluginInterface *interface);
    void message(const QString &str);

private:
    std::unique_ptr<AbstractGenericPluginInterfacePrivate> const d;
};
}
