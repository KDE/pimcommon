/*
  SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef CONFIGUREPLUGINSWIDGET_H
#define CONFIGUREPLUGINSWIDGET_H

#include <QWidget>
#include "pimcommon_export.h"
class QSplitter;
class QTextEdit;
class KMessageWidget;
namespace PimCommon {
class ConfigurePluginsListWidget;
/**
 * @brief The ConfigurePluginsWidget class
 * @author Laurent Montel <montel@kde.org>
 */
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
    void slotConfigChanged();
    void initLayout(ConfigurePluginsListWidget *configurePluginListWidget = nullptr);

    QSplitter *mSplitter = nullptr;
    ConfigurePluginsListWidget *mConfigureListWidget = nullptr;
    QTextEdit *mDescription = nullptr;
    KMessageWidget *mMessageWidget = nullptr;
};
}
#endif // CONFIGUREPLUGINSWIDGET_H
