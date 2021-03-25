/*
  SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "pimcommon_export.h"
#include <QWidget>
class QSplitter;
class QTextEdit;
class KMessageWidget;
namespace PimCommon
{
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
    ~ConfigurePluginsWidget() override;

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
