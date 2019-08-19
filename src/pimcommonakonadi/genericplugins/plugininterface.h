/*
  Copyright (c) 2015-2019 Montel Laurent <montel@kde.org>

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

#ifndef PLUGININTERFACE_H
#define PLUGININTERFACE_H

#include <QObject>
#include <PimCommonAkonadi/GenericPluginInterface>
#include <PimCommon/PluginUtil>
#include "pimcommonakonadi_export.h"
class KActionCollection;
class QAction;
class KXMLGUIClient;
namespace PimCommon {
class PluginInterfacePrivate;
/**
 * @brief The PluginInterface class
 * @author Laurent Montel <montel@kde.org>
 */
class PIMCOMMONAKONADI_EXPORT PluginInterface : public QObject
{
    Q_OBJECT
public:
    explicit PluginInterface(QObject *parent = nullptr);
    ~PluginInterface();

    void setParentWidget(QWidget *widget);
    QHash<PimCommon::ActionType::Type, QList<QAction *> > actionsType();
    void createPluginInterface();

    void setPluginName(const QString &name);
    void setServiceTypeName(const QString &name);
    void initializePlugins();
    virtual void initializeInterfaceRequires(AbstractGenericPluginInterface *interface);
    static QString actionXmlExtension(PimCommon::ActionType::Type type);

    void initializePluginActions(const QString &prefix, KXMLGUIClient *guiClient);
    void updateActions(int numberOfSelectedItems, int numberOfSelectedCollections);

    void setActionCollection(KActionCollection *ac);

    Q_REQUIRED_RESULT QVector<PimCommon::PluginUtilData> pluginsDataList() const;
    Q_REQUIRED_RESULT QString configGroupName() const;
    Q_REQUIRED_RESULT QString configPrefixSettingKey() const;

    PimCommon::GenericPlugin *pluginFromIdentifier(const QString &id);
private Q_SLOTS:
    void slotPluginActivated(AbstractGenericPluginInterface *interface);

private:
    PluginInterfacePrivate *const d;
};
}

#endif // PLUGININTERFACE_H
