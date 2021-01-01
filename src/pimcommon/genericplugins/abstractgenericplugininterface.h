/*
  SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef AbstractGENERICPLUGININTERFACE_H
#define AbstractGENERICPLUGININTERFACE_H
#include <QObject>
#include "pimcommon_export.h"
class QAction;
class KActionCollection;
namespace PimCommon {
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
        Folder = 7
    };
    ActionType()
    {
    }

    ActionType(QAction *action, Type type);
    Q_REQUIRED_RESULT QAction *action() const;
    Q_REQUIRED_RESULT Type type() const;

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
    ~AbstractGenericPluginInterface();

    void setParentWidget(QWidget *parent);
    Q_REQUIRED_RESULT QWidget *parentWidget() const;

    void setPlugin(AbstractGenericPlugin *plugin);
    Q_REQUIRED_RESULT AbstractGenericPlugin *plugin() const;

    virtual void createAction(KActionCollection *ac) = 0;
    virtual void exec() = 0;

    virtual void showConfigureDialog(QWidget *parentWidget = nullptr);

Q_SIGNALS:
    void emitPluginActivated(PimCommon::AbstractGenericPluginInterface *interface);
    void message(const QString &str);

private:
    AbstractGenericPluginInterfacePrivate *const d;
};
}
#endif // AbstractGENERICPLUGININTERFACE_H
