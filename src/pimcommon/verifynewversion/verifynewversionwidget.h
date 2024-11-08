/*
   SPDX-FileCopyrightText: 2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once
#include "pimcommon_export.h"
#include <QMap>
#include <QObject>
class QAction;
namespace PimCommon
{
class PIMCOMMON_EXPORT VerifyNewVersionWidget : public QObject
{
    Q_OBJECT
public:
    enum class OsVersion : uint8_t {
        Unknown,
        Windows,
        MacOsArm64,
        MacOs,
    };

    explicit VerifyNewVersionWidget(QObject *parent = nullptr);
    ~VerifyNewVersionWidget() override;

    [[nodiscard]] bool canVerifyNewVersion() const;

    [[nodiscard]] QAction *verifyNewVersionAction();

    void addOsUrlInfo(VerifyNewVersionWidget::OsVersion os, const QString &url);

private:
    PIMCOMMON_NO_EXPORT void slotVerifyNewVersion();
    QMap<VerifyNewVersionWidget::OsVersion, QString> mUrls;
    QAction *mVerifyNewVersionAction = nullptr;
};
}
