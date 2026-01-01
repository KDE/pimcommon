/*
  SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "plugininterface.h"

#include "pimcommonakonadi_debug.h"
#include <PimCommon/GenericPluginManager>

#include <KActionCollection>
#include <KXMLGUIClient>
#include <QAction>

#include <PimCommon/GenericPlugin>

using namespace PimCommon;

class PimCommon::PluginInterfacePrivate
{
public:
    PluginInterfacePrivate() = default;

    QString mPluginName;
    QString mPluginDirectory;
    QWidget *mParentWidget = nullptr;
    KActionCollection *mActionCollection = nullptr;
    QList<PimCommon::GenericPluginInterface *> mListGenericInterface;
    GenericPluginManager *mGenericPluginManager = nullptr;
};

PluginInterface::PluginInterface(QObject *parent)
    : QObject(parent)
    , d(new PimCommon::PluginInterfacePrivate)
{
    d->mGenericPluginManager = new GenericPluginManager(this);
}

PluginInterface::~PluginInterface() = default;

void PimCommon::PluginInterface::setActionCollection(KActionCollection *ac)
{
    d->mActionCollection = ac;
}

void PluginInterface::initializePlugins()
{
    d->mGenericPluginManager->setPluginName(d->mPluginName);
    d->mGenericPluginManager->setPluginDirectory(d->mPluginDirectory);
    if (!d->mGenericPluginManager->initializePlugins()) {
        qCDebug(PIMCOMMONAKONADI_LOG) << " Impossible to initialize plugins";
    }
}

void PluginInterface::setPluginName(const QString &name)
{
    d->mPluginName = name;
}

void PluginInterface::setPluginDirectory(const QString &name)
{
    d->mPluginDirectory = name;
}

void PluginInterface::createPluginInterface()
{
    if (!d->mActionCollection) {
        qCWarning(PIMCOMMONAKONADI_LOG) << "Missing action collection";
        return;
    }
    const auto pluginsList = d->mGenericPluginManager->pluginsList();
    for (PimCommon::GenericPlugin *plugin : pluginsList) {
        if (plugin->isEnabled()) {
            auto interface = static_cast<PimCommon::GenericPluginInterface *>(plugin->createInterface(this));
            interface->setParentWidget(d->mParentWidget);
            // Add parent before creating action
            interface->createAction(d->mActionCollection);
            interface->setPlugin(plugin);
            connect(interface, &PimCommon::GenericPluginInterface::emitPluginActivated, this, &PluginInterface::slotPluginActivated);
            d->mListGenericInterface.append(interface);
        }
    }
}

bool PluginInterface::initializeInterfaceRequires(PimCommon::AbstractGenericPluginInterface *interface)
{
    Q_UNUSED(interface)
    return true;
}

QString PluginInterface::actionXmlExtension(ActionType::Type type)
{
    switch (type) {
    case PimCommon::ActionType::Tools:
        return QStringLiteral("_plugins_tools");
    case PimCommon::ActionType::Edit:
        return QStringLiteral("_plugins_edit");
    case PimCommon::ActionType::File:
        return QStringLiteral("_plugins_file");
    case PimCommon::ActionType::Action:
        return QStringLiteral("_plugins_actions");
    case PimCommon::ActionType::PopupMenu:
        return QStringLiteral("_popupmenu_actions");
    case PimCommon::ActionType::ToolBar:
        return QStringLiteral("_toolbar_actions");
    case PimCommon::ActionType::Message:
        return QStringLiteral("_plugins_message");
    case PimCommon::ActionType::Folder:
        return QStringLiteral("_plugins_folder");
    }
    return {};
}

void PluginInterface::slotPluginActivated(PimCommon::AbstractGenericPluginInterface *interface)
{
    if (interface) {
        if (initializeInterfaceRequires(interface)) {
            interface->exec();
        }
    }
}

void PluginInterface::setParentWidget(QWidget *widget)
{
    d->mParentWidget = widget;
}

void PluginInterface::clearPluginActions(const QString &prefix, KXMLGUIClient *guiClient)
{
    if (guiClient->factory()) {
        QHashIterator<PimCommon::ActionType::Type, QList<QAction *>> localActionsType(actionsType());
        while (localActionsType.hasNext()) {
            localActionsType.next();
            QList<QAction *> lst = localActionsType.value();
            if (!lst.isEmpty()) {
                const QString actionlistname = prefix + PimCommon::PluginInterface::actionXmlExtension(localActionsType.key());
                guiClient->unplugActionList(actionlistname);
            }
        }
    }
}

void PluginInterface::initializePluginActions(const QString &prefix, KXMLGUIClient *guiClient)
{
    if (guiClient->factory()) {
        QHashIterator<PimCommon::ActionType::Type, QList<QAction *>> localActionsType(actionsType());
        while (localActionsType.hasNext()) {
            localActionsType.next();
            QList<QAction *> lst = localActionsType.value();
            if (!lst.isEmpty()) {
                const QString actionlistname = prefix + PimCommon::PluginInterface::actionXmlExtension(localActionsType.key());
                guiClient->unplugActionList(actionlistname);
                guiClient->plugActionList(actionlistname, lst);
            }
        }
    }
}

void PluginInterface::updateActions(int numberOfSelectedItems, int numberOfSelectedCollections)
{
    for (PimCommon::GenericPluginInterface *interface : std::as_const(d->mListGenericInterface)) {
        interface->updateActions(numberOfSelectedItems, numberOfSelectedCollections);
    }
}

QHash<PimCommon::ActionType::Type, QList<QAction *>> PluginInterface::actionsType()
{
    QHash<PimCommon::ActionType::Type, QList<QAction *>> listType;
    for (PimCommon::GenericPluginInterface *interface : std::as_const(d->mListGenericInterface)) {
        const auto actionTypes = interface->actionTypes();
        for (const PimCommon::ActionType &actionType : actionTypes) {
            PimCommon::ActionType::Type type = actionType.type();
            QList<QAction *> lst = listType.value(type);
            if (!lst.isEmpty()) {
                auto act = new QAction(this);
                act->setSeparator(true);
                lst << act << actionType.action();
                listType.insert(type, lst);
            } else {
                listType.insert(type, QList<QAction *>() << actionType.action());
            }
            if (interface->plugin()->hasPopupMenuSupport()) {
                type = PimCommon::ActionType::PopupMenu;
                lst = listType.value(type);
                if (!lst.isEmpty()) {
                    auto act = new QAction(this);
                    act->setSeparator(true);
                    lst << act << actionType.action();
                    listType.insert(type, lst);
                } else {
                    listType.insert(type, QList<QAction *>() << actionType.action());
                }
            }
            if (interface->plugin()->hasToolBarSupport()) {
                type = PimCommon::ActionType::ToolBar;
                lst = listType.value(type);
                if (!lst.isEmpty()) {
                    auto act = new QAction(this);
                    act->setSeparator(true);
                    lst << act << actionType.action();
                    listType.insert(type, lst);
                } else {
                    listType.insert(type, QList<QAction *>() << actionType.action());
                }
            }
        }
    }

    return listType;
}

QList<TextAddonsWidgets::PluginUtilData> PluginInterface::pluginsDataList() const
{
    return d->mGenericPluginManager->pluginsDataList();
}

QString PluginInterface::configGroupName() const
{
    return d->mGenericPluginManager->configGroupName();
}

QString PluginInterface::configPrefixSettingKey() const
{
    return d->mGenericPluginManager->configPrefixSettingKey();
}

PimCommon::GenericPlugin *PluginInterface::pluginFromIdentifier(const QString &id)
{
    return d->mGenericPluginManager->pluginFromIdentifier(id);
}

#include "moc_plugininterface.cpp"
