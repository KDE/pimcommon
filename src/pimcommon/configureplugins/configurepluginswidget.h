/*
  SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "pimcommon_export.h"
#include <QWidget>
#include <TextAddonsWidgets/ConfigurePluginsWidget>
class KMessageWidget;
namespace PimCommon
{
/**
 * @brief The ConfigurePluginsWidget class
 * @author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT ConfigurePluginsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ConfigurePluginsWidget(QWidget *parent = nullptr);
    explicit ConfigurePluginsWidget(TextAddonsWidgets::ConfigurePluginsWidget *configurePluginListWidget, QWidget *parent = nullptr);
    ~ConfigurePluginsWidget() override;

    void save();
    void defaults();
    void doLoadFromGlobalSettings();
    void doResetToDefaultsOther();

Q_SIGNALS:
    void wasChanged(bool changed);

private:
    PIMCOMMON_NO_EXPORT void initialize();
    PIMCOMMON_NO_EXPORT void slotConfigChanged();
    PIMCOMMON_NO_EXPORT void initLayout(TextAddonsWidgets::ConfigurePluginsWidget *configurePluginListWidget = nullptr);

    TextAddonsWidgets::ConfigurePluginsWidget *mConfigureListWidget = nullptr;
};
}
