/*
  Copyright (c) 2016 Montel Laurent <montel@kde.org>

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

#ifndef CONFIGUREPLUGINSLISTWIDGET_H
#define CONFIGUREPLUGINSLISTWIDGET_H

#include <QWidget>
#include "pimcommon_export.h"
#include "pimcommon/pluginutil.h"

#include <QTreeWidgetItem>
class QTreeWidget;
namespace PimCommon
{
class PIMCOMMON_EXPORT ConfigurePluginsListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ConfigurePluginsListWidget(QWidget *parent = Q_NULLPTR);
    ~ConfigurePluginsListWidget();

    virtual void save();
    virtual void doLoadFromGlobalSettings();
    virtual void doResetToDefaultsOther();
    virtual void initialize();
Q_SIGNALS:
    void descriptionChanged(const QString &description);
    void changed();

private:
    void slotItemSelectionChanged();
    void slotItemChanged(QTreeWidgetItem *item, int column);

protected:
    class PluginItem : public QTreeWidgetItem
    {
    public:
        PluginItem(QTreeWidgetItem *parent)
            : QTreeWidgetItem(parent),
              mEnableByDefault(false)
        {

        }
        QString mIdentifier;
        QString mDescription;
        bool mEnableByDefault;
    };
    void savePlugins(const QString &groupName, const QString &prefixSettingKey, const QList<PluginItem *> &listItems);
    void fillTopItems(const QVector<PimCommon::PluginUtilData> &lst, const QString &topLevelItemName, const QString &groupName, const QString &prefixKey, QList<PluginItem *> &itemsList);
    void changeState(const QList<PluginItem *> &items);

    QTreeWidget *mListWidget;
};
}

#endif // CONFIGUREPLUGINSLISTWIDGET_H
