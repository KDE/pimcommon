/*
  SPDX-FileCopyrightText: 2014-2023 Laurent Montel <montel@kde.org>
  SPDX-FileCopyrightText: 2021 Carl Schwan <carlschwan@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "incidencesforwidget.h"
#include <KLocalizedString>

using namespace PimCommon;
IncidencesForWidget::IncidencesForWidget(QWidget *parent)
    : QComboBox(parent)
{
    addItem(i18n("Nobody"));
    addItem(i18n("Admins of This Folder"));
    addItem(i18n("All Readers of This Folder"));

    setObjectName(QStringLiteral("contentstypecombobox"));
    const QString whatsThisForMyOwnFolders = i18n(
        "This setting defines which users sharing "
        "this folder should get \"busy\" periods in their freebusy lists "
        "and should see the alarms for the events or tasks in this folder. "
        "The setting applies to Calendar and Task folders only "
        "(for tasks, this setting is only used for alarms).\n\n"
        "Example use cases: if the boss shares a folder with his secretary, "
        "only the boss should be marked as busy for his meetings, so he should "
        "select \"Admins\", since the secretary has no admin rights on the folder.\n"
        "On the other hand if a working group shares a Calendar for "
        "group meetings, all readers of the folders should be marked "
        "as busy for meetings.\n"
        "A company-wide folder with optional events in it would use \"Nobody\" "
        "since it is not known who will go to those events.");
    setWhatsThis(whatsThisForMyOwnFolders);
}

IncidencesForWidget::~IncidencesForWidget() = default;

QString IncidencesForWidget::labelName()
{
    return i18n("Generate free/&busy and activate alarms for:");
}

#include "moc_incidencesforwidget.cpp"
