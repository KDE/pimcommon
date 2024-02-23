/*
  SPDX-FileCopyrightText: 2018-2024 Laurent Montel <montel@kde.org>

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

    [[nodiscard]] virtual QByteArray text() = 0;
    [[nodiscard]] QMenu *menu() const;

Q_SIGNALS:
    void shareError(const QString &message);
    void shareSuccess(const QString &url);

private:
    PIMCOMMON_NO_EXPORT void slotInitializeShareMenu();
    PIMCOMMON_NO_EXPORT void slotShareActionFinished(const QJsonObject &output, int error, const QString &message);
    QWidget *const mParentWidget;
    Purpose::Menu *const mShareMenu;
    QTemporaryFile *mTemporaryShareFile = nullptr;
};
}
