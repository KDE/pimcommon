/*
  SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "pimcommon_export.h"
#include <QObject>
namespace PimCommon
{
class AbstractGenericPluginInterface;
/**
 * @brief The AbstractGenericPlugin class
 * @author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT AbstractGenericPlugin : public QObject
{
    Q_OBJECT
public:
    explicit AbstractGenericPlugin(QObject *parent = nullptr);
    ~AbstractGenericPlugin() override;

    virtual PimCommon::AbstractGenericPluginInterface *createInterface(QObject *parent = nullptr) = 0;
    [[nodiscard]] virtual bool hasPopupMenuSupport() const;
    [[nodiscard]] virtual bool hasToolBarSupport() const;
    [[nodiscard]] virtual bool hasConfigureDialog() const;
    [[nodiscard]] virtual bool hasStatusBarSupport() const;

    virtual void showConfigureDialog(QWidget *parent = nullptr);

    void setIsEnabled(bool enabled);
    [[nodiscard]] bool isEnabled() const;

Q_SIGNALS:
    void configChanged();

private:
    bool mIsEnabled = true;
};
}
