/*
  SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef AbstractGENERICPLUGIN_H
#define AbstractGENERICPLUGIN_H

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
    Q_REQUIRED_RESULT virtual bool hasPopupMenuSupport() const;
    Q_REQUIRED_RESULT virtual bool hasToolBarSupport() const;
    Q_REQUIRED_RESULT virtual bool hasConfigureDialog() const;
    Q_REQUIRED_RESULT virtual bool hasStatusBarSupport() const;

    virtual void showConfigureDialog(QWidget *parent = nullptr);

    void setIsEnabled(bool enabled);
    Q_REQUIRED_RESULT bool isEnabled() const;

Q_SIGNALS:
    void configChanged();

private:
    bool mIsEnabled = true;
};
}
#endif // AbstractGENERICPLUGIN_H
