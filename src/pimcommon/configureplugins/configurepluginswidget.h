/*
  Copyright (c) 2016-2017 Montel Laurent <montel@kde.org>

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

#ifndef CONFIGUREPLUGINSWIDGET_H
#define CONFIGUREPLUGINSWIDGET_H

#include <QWidget>
#include "pimcommon_export.h"
class QSplitter;
class QTextEdit;
namespace PimCommon {
class ConfigurePluginsListWidget;
class PIMCOMMON_EXPORT ConfigurePluginsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ConfigurePluginsWidget(QWidget *parent = nullptr);
    explicit ConfigurePluginsWidget(ConfigurePluginsListWidget *configurePluginListWidget, QWidget *parent = nullptr);
    ~ConfigurePluginsWidget();

    void save();
    void defaults();
    void doLoadFromGlobalSettings();
    void doResetToDefaultsOther();

Q_SIGNALS:
    void changed();

private:
    void initialize();
    void readConfig();
    void writeConfig();
    void initLayout(ConfigurePluginsListWidget *configurePluginListWidget = nullptr);

    QSplitter *mSplitter;
    ConfigurePluginsListWidget *mConfigureListWidget;
    QTextEdit *mDescription;
};
}
#endif // CONFIGUREPLUGINSWIDGET_H
