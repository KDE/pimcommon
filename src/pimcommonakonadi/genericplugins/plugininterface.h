/*
  SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "pimcommonakonadi_export.h"
#include <PimCommon/PluginUtil>
#include <PimCommonAkonadi/GenericPluginInterface>
#include <QObject>
#include <TextAddonsWidgets/PluginUtil>
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
    [[nodiscard]] QHash<PimCommon::ActionType::Type, QList<QAction *>> actionsType();
    void createPluginInterface();

    void setPluginName(const QString &name);
    void setPluginDirectory(const QString &name);
    void initializePlugins();
    virtual bool initializeInterfaceRequires(AbstractGenericPluginInterface *interface);
    [[nodiscard]] static QString actionXmlExtension(PimCommon::ActionType::Type type);

    void initializePluginActions(const QString &prefix, KXMLGUIClient *guiClient);
    void updateActions(int numberOfSelectedItems, int numberOfSelectedCollections);

    void setActionCollection(KActionCollection *ac);

    [[nodiscard]] QList<TextAddonsWidgets::PluginUtilData> pluginsDataList() const;
    [[nodiscard]] QString configGroupName() const;
    [[nodiscard]] QString configPrefixSettingKey() const;

    [[nodiscard]] PimCommon::GenericPlugin *pluginFromIdentifier(const QString &id);
    void clearPluginActions(const QString &prefix, KXMLGUIClient *guiClient);

private:
    PIMCOMMONAKONADI_NO_EXPORT void slotPluginActivated(PimCommon::AbstractGenericPluginInterface *interface);
    std::unique_ptr<PluginInterfacePrivate> const d;
};
}
