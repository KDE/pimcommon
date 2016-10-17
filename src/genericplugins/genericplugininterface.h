/*
  Copyright (c) 2015-2016 Montel Laurent <montel@kde.org>

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

#ifndef GENERICPLUGININTERFACE_H
#define GENERICPLUGININTERFACE_H

#include <QObject>
#include "abstractgenericplugininterface.h"
#include "pimcommon_export.h"
#include <AkonadiCore/Item>
class QAction;
class KActionCollection;
namespace PimCommon
{
class GenericPlugin;
class PIMCOMMON_EXPORT ActionType
{
public:
    enum Type {
        Tools = 0,
        Edit = 1,
        File = 2,
        Action = 3,
        PopupMenu = 4,
        ToolBar = 5
    };
    ActionType()
        : mAction(Q_NULLPTR),
          mType(Tools)
    {

    }

    ActionType(QAction *action, Type type);
    QAction *action() const;
    Type type() const;

private:
    QAction *mAction;
    Type mType;
};

class GenericPluginInterfacePrivate;
class PIMCOMMON_EXPORT GenericPluginInterface : public AbstractGenericPluginInterface
{
    Q_OBJECT
public:
    explicit GenericPluginInterface(QObject *parent = Q_NULLPTR);
    ~GenericPluginInterface();

    enum RequireType {
        None = 0,
        CurrentItems = 1,
        Items = 2,
        CurrentCollection = 3,
        Collections = 4
    };
    Q_ENUMS(RequireType)
    Q_DECLARE_FLAGS(RequireTypes, RequireType)

    void setActionType(const ActionType &type);
    ActionType actionType() const;

    virtual void setCurrentItems(const Akonadi::Item::List &items);
    virtual void setItems(const Akonadi::Item::List &items);
    virtual void setCurrentCollection(const Akonadi::Collection &col);
    virtual void setCollections(const Akonadi::Collection::List &cols);

    virtual GenericPluginInterface::RequireTypes requires() const;

    virtual void updateActions(int numberOfSelectedItems, int numberOfSelectedCollections);

private:
    GenericPluginInterfacePrivate *const d;
};
}
Q_DECLARE_TYPEINFO(PimCommon::ActionType, Q_MOVABLE_TYPE);
#endif // GENERICPLUGININTERFACE_H
