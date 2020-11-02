/*
  SPDX-FileCopyrightText: 2014-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "incidencesforwidget.h"
#include <QLabel>
#include <QHBoxLayout>
#include <KLocalizedString>
#include <QComboBox>

using namespace PimCommon;
class PimCommon::IncidencesForWidgetPrivate
{
public:
    IncidencesForWidgetPrivate()
    {
    }

    QComboBox *mIncidencesForComboBox = nullptr;
};
IncidencesForWidget::IncidencesForWidget(QWidget *parent)
    : QWidget(parent)
    , d(new PimCommon::IncidencesForWidgetPrivate)
{
    auto *hbox = new QHBoxLayout(this);
    hbox->setContentsMargins(0, 0, 0, 0);

    QLabel *label = new QLabel(i18n("Generate free/&busy and activate alarms for:"), this);
    label->setObjectName(QStringLiteral("contentstypelabel"));
    hbox->addWidget(label);

    d->mIncidencesForComboBox = new QComboBox(this);
    label->setBuddy(d->mIncidencesForComboBox);
    hbox->addWidget(d->mIncidencesForComboBox);

    d->mIncidencesForComboBox->addItem(i18n("Nobody"));
    d->mIncidencesForComboBox->addItem(i18n("Admins of This Folder"));
    d->mIncidencesForComboBox->addItem(i18n("All Readers of This Folder"));
    const QString whatsThisForMyOwnFolders
        = i18n("This setting defines which users sharing "
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

    d->mIncidencesForComboBox->setObjectName(QStringLiteral("contentstypecombobox"));
    d->mIncidencesForComboBox->setWhatsThis(whatsThisForMyOwnFolders);
    connect(d->mIncidencesForComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &IncidencesForWidget::currentIndexChanged);
}

IncidencesForWidget::~IncidencesForWidget()
{
    delete d;
}

int IncidencesForWidget::currentIndex() const
{
    return d->mIncidencesForComboBox->currentIndex();
}

void IncidencesForWidget::setCurrentIndex(int index)
{
    d->mIncidencesForComboBox->setCurrentIndex(index);
}
