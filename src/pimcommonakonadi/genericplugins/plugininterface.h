/*
  SPDX-FileCopyrightText: 2015-2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "pimcommonakonadi_export.h"
#include <PimCommon/PluginUtil>
#include <PimCommonAkonadi/GenericPluginInterface>
#include <QObject>
class KActionCollection;
class QAction;
class KXMLGUIClient;
namespace PimCommon
{
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
    ~PluginInterface() override;

    void setParentWidget(QWidget *widget);
    Q_REQUIRED_RESULT QHash<PimCommon::ActionType::Type, QList<QAction *>> actionsType();
    void createPluginInterface();

    void setPluginName(const QString &name);
    void setPluginDirectory(const QString &name);
    void initializePlugins();
    virtual bool initializeInterfaceRequires(AbstractGenericPluginInterface *interface);
    static QString actionXmlExtension(PimCommon::ActionType::Type type);

    void initializePluginActions(const QString &prefix, KXMLGUIClient *guiClient);
    void updateActions(int numberOfSelectedItems, int numberOfSelectedCollections);

    void setActionCollection(KActionCollection *ac);

    Q_REQUIRED_RESULT QVector<PimCommon::PluginUtilData> pluginsDataList() const;
    Q_REQUIRED_RESULT QString configGroupName() const;
    Q_REQUIRED_RESULT QString configPrefixSettingKey() const;

    PimCommon::GenericPlugin *pluginFromIdentifier(const QString &id);
    void clearPluginActions(const QString &prefix, KXMLGUIClient *guiClient);
private Q_SLOTS:
    void slotPluginActivated(PimCommon::AbstractGenericPluginInterface *interface);

private:
    std::unique_ptr<PluginInterfacePrivate> const d;
};
}
