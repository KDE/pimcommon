/*
   SPDX-FileCopyrightText: 2024-2026 Laurent Montel <montel@kde.org>

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
/*!
 * \class PimCommonActivities::ActivitiesBaseManager
 * \brief The ActivitiesBaseManager class manages activities for PIM components
 * \inmodule PimCommonActivities
 * \inheaderfile PimCommonActivities/ActivitiesBaseManager
 * \author Laurent Montel <montel@kde.org>
 */
class PIMCOMMONACTIVITIES_EXPORT ActivitiesBaseManager : public QObject
{
    Q_OBJECT
public:
    struct ActivitySettings {
        QStringList activities;
        bool enabled = false;
        /*!
         * Checks if the given string is contained in the activities list.
         * @param str The string to check
         * @return true if the string is in the activities list, false otherwise
         */
        [[nodiscard]] bool contains(const QString &str) const;

        /*!
         * Changes the activities list based on add/remove operation.
         * @param added true if adding the activity, false if removing
         * @param currentActivity The activity to add or remove
         */
        void changeActivities(bool added, const QString &currentActivity);
    };
    /*!
     * Constructs an ActivitiesBaseManager.
     * @param parent The parent QObject
     */
    explicit ActivitiesBaseManager(QObject *parent = nullptr);
    /*!
     * Destructs the ActivitiesBaseManager.
     */
    ~ActivitiesBaseManager() override;

    /*!
     * Checks if the given list of activities contains the current activity.
     * @param lst The list of activities to check
     * @return true if the current activity is in the list, false otherwise
     */
    [[nodiscard]] bool isInCurrentActivity(const QStringList &lst) const;

    /*!
     * Returns the current activity.
     * @return The current activity identifier
     */
    [[nodiscard]] QString currentActivity() const;

    /*!
     * Returns whether activities support is enabled.
     * @return true if enabled, false otherwise
     */
    [[nodiscard]] bool enabled() const;
    /*!
     * Sets whether activities support is enabled.
     * @param newEnabled true to enable, false to disable
     */
    void setEnabled(bool newEnabled);

Q_SIGNALS:
    /*!
     * Emitted when activities have changed.
     */
    void activitiesChanged();

private:
    KActivities::Consumer *const mActivitiesConsumer;
    bool mEnabled = false;
};
}
PIMCOMMONACTIVITIES_EXPORT QDebug operator<<(QDebug d, const PimCommonActivities::ActivitiesBaseManager::ActivitySettings &t);
