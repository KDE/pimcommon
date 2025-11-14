/*
  SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "pimcommon_export.h"
#include <PimCommon/PluginUtil>
#include <QWidget>

#include <QTreeWidgetItem>
#include <TextAddonsWidgets/ConfigurePluginsWidget>
namespace PimCommon
{
/**
 * @brief The ConfigurePluginsListWidget class
 * @author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT ConfigurePluginsListWidget : public TextAddonsWidgets::ConfigurePluginsWidget
{
    Q_OBJECT
public:
    explicit ConfigurePluginsListWidget(QWidget *parent = nullptr);
    ~ConfigurePluginsListWidget() override;
};
}
