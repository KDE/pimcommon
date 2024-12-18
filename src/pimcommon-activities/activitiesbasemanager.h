/*
   SPDX-FileCopyrightText: 2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "pimcommonactivities_export.h"
#include <QObject>
namespace KActivities
{
class Consumer;
}
namespace PimCommonActivities
{
class PIMCOMMONACTIVITIES_EXPORT ActivitiesBaseManager : public QObject
{
    Q_OBJECT
public:
    struct ActivitySettings {
        QStringList activities;
        bool enabled = false;
        [[nodiscard]] bool contains(const QString &str) const;

        void changeActivities(bool added, const QString &currentActivity);
    };

    explicit ActivitiesBaseManager(QObject *parent = nullptr);
    ~ActivitiesBaseManager() override;
    [[nodiscard]] virtual bool enabled() const = 0;

    [[nodiscard]] bool isInCurrentActivity(const QStringList &lst) const;

    [[nodiscard]] QString currentActivity() const;
Q_SIGNALS:
    void activitiesChanged();

private:
    KActivities::Consumer *const mActivitiesConsumer;
};
}
PIMCOMMONACTIVITIES_EXPORT QDebug operator<<(QDebug d, const PimCommonActivities::ActivitiesBaseManager::ActivitySettings &t);
