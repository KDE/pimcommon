/*
   SPDX-FileCopyrightText: 2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "activitiesbasemanager.h"
#include "pimcommonactivities_debug.h"
#include <PlasmaActivities/Consumer>
using namespace PimCommonActivities;
ActivitiesBaseManager::ActivitiesBaseManager(QObject *parent)
    : QObject{parent}
    , mActivitiesConsumer(new KActivities::Consumer(this))
{
    connect(mActivitiesConsumer, &KActivities::Consumer::currentActivityChanged, this, [this](const QString &activityId) {
        qCDebug(PIMCOMMONACTIVITIES_LOG) << " switch to activity " << activityId;
        Q_EMIT activitiesChanged();
    });
    connect(mActivitiesConsumer, &KActivities::Consumer::activityRemoved, this, [this](const QString &activityId) {
        qCDebug(PIMCOMMONACTIVITIES_LOG) << " Activity removed " << activityId;
        Q_EMIT activitiesChanged();
    });
    connect(mActivitiesConsumer, &KActivities::Consumer::serviceStatusChanged, this, &ActivitiesBaseManager::activitiesChanged);
    if (mActivitiesConsumer->serviceStatus() != KActivities::Consumer::ServiceStatus::Running) {
        qCWarning(PIMCOMMONACTIVITIES_LOG) << "Plasma activities is not running: " << mActivitiesConsumer->serviceStatus();
    }
}

ActivitiesBaseManager::~ActivitiesBaseManager() = default;

bool ActivitiesBaseManager::isInCurrentActivity(const QStringList &lst) const
{
    if (mActivitiesConsumer->serviceStatus() == KActivities::Consumer::ServiceStatus::Running) {
        if (lst.contains(mActivitiesConsumer->currentActivity())) {
            return true;
        } else {
            const QStringList activities = mActivitiesConsumer->activities();
            auto index = std::find_if(activities.constBegin(), activities.constEnd(), [lst](const QString &str) {
                return lst.contains(str);
            });
            // Account doesn't contains valid activities => show it.
            if (index == activities.constEnd()) {
                return true;
            }
            return false;
        }
    } else {
        return true;
    }
}

QString ActivitiesBaseManager::currentActivity() const
{
    return mActivitiesConsumer->currentActivity();
}

QDebug operator<<(QDebug d, const PimCommonActivities::ActivitiesBaseManager::ActivitySettings &t)
{
    d << "enabled: " << t.enabled;
    d << "activities: " << t.activities;
    return d;
}
#include "moc_activitiesbasemanager.cpp"
