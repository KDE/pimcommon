/*
  Copyright (c) 2015 Montel Laurent <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License, version 2, as
  published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "plugininterface.h"
#include "genericpluginmanager.h"
#include "pimcommon_debug.h"

#include <KActionCollection>

#include "genericplugin.h"

using namespace PimCommon;

class PimCommon::PluginInterfacePrivate
{
public:
    PluginInterfacePrivate(KActionCollection *ac)
        : mParentWidget(Q_NULLPTR),
          mActionCollection(ac)
    {

    }
    QString mPluginName;
    QString mServiceTypeName;
    QWidget *mParentWidget;
    KActionCollection *mActionCollection;
    QVector<PimCommon::GenericPluginInterface *> mListGenericInterface;
};

PluginInterface::PluginInterface(KActionCollection *ac, QObject *parent)
    : QObject(parent),
      d(new PimCommon::PluginInterfacePrivate(ac))
{
}

PluginInterface::~PluginInterface()
{
    delete d;
}

void PluginInterface::initializePlugins()
{
    PimCommon::GenericPluginManager::self()->setPluginName(d->mPluginName);
    PimCommon::GenericPluginManager::self()->setServiceTypeName(d->mServiceTypeName);
    if (!PimCommon::GenericPluginManager::self()->initializePlugins()) {
        qCDebug(PIMCOMMON_LOG) << " Impossible to initialize plugins";
    }
}

void PluginInterface::setPluginName(const QString &name)
{
    d->mPluginName = name;
}

void PluginInterface::setServiceTypeName(const QString &name)
{
    d->mServiceTypeName = name;
}

void PluginInterface::createPluginInterface()
{
    Q_FOREACH(PimCommon::GenericPlugin *plugin, PimCommon::GenericPluginManager::self()->pluginsList()) {
        PimCommon::GenericPluginInterface *interface = plugin->createInterface(d->mActionCollection, d->mParentWidget);
        connect(interface, &PimCommon::GenericPluginInterface::emitPluginActivated, this, &PluginInterface::slotPluginActivated);
        d->mListGenericInterface.append(interface);
    }
}

void PluginInterface::initializeInterfaceRequires(PimCommon::GenericPluginInterface *interface)
{
    Q_UNUSED(interface)
}

void PluginInterface::slotPluginActivated(PimCommon::GenericPluginInterface *interface)
{
    initializeInterfaceRequires(interface);
    if (interface) {
        interface->exec();
    }
}

void PluginInterface::setParentWidget(QWidget *widget)
{
    d->mParentWidget = widget;
}

QHash<PimCommon::ActionType::Type, QList<QAction *> > PluginInterface::actionsType() const
{
    QHash<PimCommon::ActionType::Type, QList<QAction *> > listType;
    Q_FOREACH(PimCommon::GenericPluginInterface *interface, d->mListGenericInterface) {
        PimCommon::ActionType actionType = interface->actionType();
        PimCommon::ActionType::Type type = actionType.type();
        if (listType.contains(type)) {
            QList<QAction *> lst = listType.value(type);
            lst << actionType.action();
            listType.insert(type, lst);
        } else {
            listType.insert(type, QList<QAction *>() << actionType.action());
        }
        if (interface->hasPopupMenuSupport()) {
            type = PimCommon::ActionType::PopupMenu;
            if (listType.contains(type)) {
                QList<QAction *> lst = listType.value(type);
                lst << actionType.action();
                listType.insert(type, lst);
            } else {
                listType.insert(type, QList<QAction *>() << actionType.action());
            }
        }
    }

    return listType;
}
