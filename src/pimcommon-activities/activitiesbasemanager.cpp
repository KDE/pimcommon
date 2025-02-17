/*
   SPDX-FileCopyrightText: 2024-2025 Laurent Montel <montel@kde.org>

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

bool ActivitiesBaseManager::enabled() const
{
    return mEnabled;
}

void ActivitiesBaseManager::setEnabled(bool newEnabled)
{
    if (mEnabled != newEnabled) {
        mEnabled = newEnabled;
        Q_EMIT activitiesChanged();
    }
}

QDebug operator<<(QDebug d, const PimCommonActivities::ActivitiesBaseManager::ActivitySettings &t)
{
    d << "enabled: " << t.enabled;
    d << "activities: " << t.activities;
    return d;
}

bool ActivitiesBaseManager::ActivitySettings::contains(const QString &str) const
{
    return activities.contains(str);
}

void ActivitiesBaseManager::ActivitySettings::changeActivities(bool added, const QString &currentActivity)
{
    if (added) {
        if (!activities.contains(currentActivity)) {
            activities.append(currentActivity);
        }
    } else {
        if (activities.contains(currentActivity)) {
            activities.removeAll(currentActivity);
        }
    }
    enabled = true;
}

#include "moc_activitiesbasemanager.cpp"
