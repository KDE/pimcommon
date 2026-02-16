/*
   SPDX-FileCopyrightText: 2024-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once
#include "activitiesbasemanager.h"
#include "pimcommonactivities_export.h"
#include <QWidget>
class QListView;
class QCheckBox;
namespace PimCommonActivities
{
/*!
 * \class PimCommonActivities::ConfigureActivitiesWidget
 * \brief The ConfigureActivitiesWidget class provides a widget for configuring activities
 * \inmodule PimCommonActivities
 * \inheaderfile PimCommonActivities/ConfigureActivitiesWidget
 * \author Laurent Montel <montel@kde.org>
 */
class PIMCOMMONACTIVITIES_EXPORT ConfigureActivitiesWidget : public QWidget
{
    Q_OBJECT
public:
    /*!
     * Constructs a ConfigureActivitiesWidget.
     * @param parent The parent widget
     */
    explicit ConfigureActivitiesWidget(QWidget *parent = nullptr);
    /*!
     * Destructs the ConfigureActivitiesWidget.
     */
    ~ConfigureActivitiesWidget() override;

    /*!
     * Returns the current activities settings.
     * @return The ActivitySettings structure with current configuration
     */
    [[nodiscard]] ActivitiesBaseManager::ActivitySettings activitiesSettings() const;
    /*!
     * Sets the activities settings.
     * @param activitySettings The ActivitySettings to apply
     */
    void setActivitiesSettings(const ActivitiesBaseManager::ActivitySettings &activitySettings);

private:
    QListView *const mListView;
    QCheckBox *const mEnableActivitiesSupport;
};
}
