/*
  SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "pimcommon_export.h"
#include <PimCommon/PluginUtil>
#include <QWidget>

#include <QTreeWidgetItem>
class QTreeWidget;
class QAction;
class KTreeWidgetSearchLineWidget;
namespace PimCommon
{
/**
 * @brief The ConfigurePluginsListWidget class
 * @author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT ConfigurePluginsListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ConfigurePluginsListWidget(QWidget *parent = nullptr);
    ~ConfigurePluginsListWidget() override;

    virtual void save();
    virtual void doLoadFromGlobalSettings();
    virtual void doResetToDefaultsOther();
    virtual void defaults();
    virtual void initialize();
    void initializeDone();
Q_SIGNALS:
    void descriptionChanged(const QString &description);
    void changed();
    void configureClicked(const QString &configureGroupName, const QString &identifier);

private:
    void slotItemSelectionChanged();
    void slotItemChanged(QTreeWidgetItem *item, int column);

protected:
    class PluginItem : public QTreeWidgetItem
    {
    public:
        explicit PluginItem(QTreeWidgetItem *parent)
            : QTreeWidgetItem(parent)
        {
        }

        QString mIdentifier;
        QString mDescription;
        bool mEnableByDefault = false;
        bool mHasConfigureSupport = false;
        bool mEnableFromUserSettings = false;
    };
    void savePlugins(const QString &groupName, const QString &prefixSettingKey, const QVector<PluginItem *> &listItems);
    void fillTopItems(const QVector<PimCommon::PluginUtilData> &lst,
                      const QString &topLevelItemName,
                      const QString &groupName,
                      const QString &prefixKey,
                      QVector<PluginItem *> &itemsList,
                      const QString &configureGroupName = QString(),
                      bool checkable = true);
    void resetToUserSettings(const QVector<PluginItem *> &items);
    void changeState(const QVector<PluginItem *> &items);

    QTreeWidget *const mListWidget;

private:
    KTreeWidgetSearchLineWidget *mTreeWidgetSearchLineEdit = nullptr;
    void slotConfigureClicked(QAction *act);
    bool mInitializeDone = false;
};
}

