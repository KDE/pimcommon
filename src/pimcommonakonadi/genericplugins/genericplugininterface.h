/*
  Copyright (c) 2015-2020 Laurent Montel <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

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
#include <PimCommon/AbstractGenericPluginInterface>
#include "pimcommonakonadi_export.h"
#include <AkonadiCore/Item>
namespace PimCommon {
class GenericPluginInterfacePrivate;
/**
 * @brief The GenericPluginInterface class
 * @author Laurent Montel <montel@kde.org>
 */
class PIMCOMMONAKONADI_EXPORT GenericPluginInterface : public AbstractGenericPluginInterface
{
    Q_OBJECT
public:
    explicit GenericPluginInterface(QObject *parent = nullptr);
    ~GenericPluginInterface();

    enum RequireType {
        None = 0,
        CurrentItems = 1,
        Items = 2,
        CurrentCollection = 3,
        Collections = 4
    };
    Q_ENUM(RequireType)
    Q_DECLARE_FLAGS(RequireTypes, RequireType)

    void setActionTypes(const QVector<ActionType> &type);
    void addActionType(ActionType type);
    Q_REQUIRED_RESULT QVector<ActionType> actionTypes() const;

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
