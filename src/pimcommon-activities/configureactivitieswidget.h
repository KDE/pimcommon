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
 * \brief The ConfigureActivitiesWidget class
 * \inmodule PimCommonActivities
 * \inheaderfile PimCommonActivities/ConfigureActivitiesWidget
 */
class PIMCOMMONACTIVITIES_EXPORT ConfigureActivitiesWidget : public QWidget
{
    Q_OBJECT
public:
    /*!
     */
    explicit ConfigureActivitiesWidget(QWidget *parent = nullptr);
    /*!
     */
    ~ConfigureActivitiesWidget() override;

    /*!
     */
    [[nodiscard]] ActivitiesBaseManager::ActivitySettings activitiesSettings() const;
    /*!
     */
    void setActivitiesSettings(const ActivitiesBaseManager::ActivitySettings &activitySettings);

private:
    QListView *const mListView;
    QCheckBox *const mEnableActivitiesSupport;
};
}
