/*
  SPDX-FileCopyrightText: 2015-2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "pimcommon_export.h"
#include <QObject>
#include <memory>
class KActionCollection;
namespace PimCommon
{
class CustomToolsWidgetNg;
class CustomToolsViewInterface;
class CustomToolsPluginPrivate;
/**
 * @brief The CustomToolsPlugin class
 * @author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT CustomToolsPlugin : public QObject
{
    Q_OBJECT
public:
    explicit CustomToolsPlugin(QObject *parent = nullptr);
    ~CustomToolsPlugin() override;

    virtual PimCommon::CustomToolsViewInterface *createView(KActionCollection *ac, CustomToolsWidgetNg *parent = nullptr) = 0;
    Q_REQUIRED_RESULT virtual QString customToolName() const = 0;

    Q_REQUIRED_RESULT virtual bool hasConfigureDialog() const;
    virtual void showConfigureDialog(QWidget *parent);

    void emitConfigChanged();

    Q_REQUIRED_RESULT virtual QString description() const;

    void setIsEnabled(bool enabled);
    Q_REQUIRED_RESULT bool isEnabled() const;

private:
    std::unique_ptr<CustomToolsPluginPrivate> const d;
};
}
