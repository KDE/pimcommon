/*
  SPDX-FileCopyrightText: 2018-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "pimcommon_export.h"
#include <QObject>
namespace Purpose
{
class Menu;
}
class QMenu;
class QTemporaryFile;
namespace PimCommon
{
/**
 * @brief The PurposeMenuWidget class
 * @author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT PurposeMenuWidget : public QObject
{
    Q_OBJECT
public:
    explicit PurposeMenuWidget(QWidget *parentWidget, QObject *parent = nullptr);
    ~PurposeMenuWidget() override;

    Q_REQUIRED_RESULT virtual QByteArray text() = 0;
    Q_REQUIRED_RESULT QMenu *menu() const;

private:
    PIMCOMMON_NO_EXPORT void slotInitializeShareMenu();
    PIMCOMMON_NO_EXPORT void slotShareActionFinished(const QJsonObject &output, int error, const QString &message);
    Purpose::Menu *mShareMenu = nullptr;
    QTemporaryFile *mTemporaryShareFile = nullptr;
    QWidget *const mParentWidget;
};
}
