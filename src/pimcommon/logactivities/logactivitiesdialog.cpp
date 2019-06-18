/*
  Copyright (C) 2017-2019 Montel Laurent <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "logactivitiesdialog.h"
#include "logactivitieswidget.h"
#include "logactivitiesmanager.h"
#include "logactivitiespurposemenuwidget.h"
#include <PimCommon/PimUtil>
#include <KLocalizedString>
#include <KConfigGroup>
#include <KSharedConfig>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QCheckBox>

using namespace PimCommon;

LogActivitiesDialog::LogActivitiesDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(i18n("Log activities"));
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));

    mLogWidget = new LogActivitiesWidget(this);
    mLogWidget->setObjectName(QStringLiteral("logwidget"));
    mainLayout->addWidget(mLogWidget);

    mEnableLogActivities = new QCheckBox(i18n("Log activities"), this);
    mEnableLogActivities->setObjectName(QStringLiteral("enablelogactivities"));
    mainLayout->addWidget(mEnableLogActivities);
    connect(mEnableLogActivities, &QCheckBox::toggled, this, &LogActivitiesDialog::slotEnableLogActivities);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Close | QDialogButtonBox::Save, this);
    buttonBox->setObjectName(QStringLiteral("buttonbox"));

    mClearButton = new QPushButton(i18n("Clear"), this);
    mClearButton->setObjectName(QStringLiteral("clearbutton"));
    buttonBox->addButton(mClearButton, QDialogButtonBox::ActionRole);
    connect(mClearButton, &QPushButton::clicked, this, &LogActivitiesDialog::slotClear);
    mSaveButton = buttonBox->button(QDialogButtonBox::Save);
    mSaveButton->setObjectName(QStringLiteral("savebutton"));
    mSaveButton->setEnabled(false);

    LogactivitiesPurposeMenuWidget *purposeMenu = new LogactivitiesPurposeMenuWidget(this, this);
    mShareButton = new QPushButton(i18n("Share..."), this);
    mShareButton->setMenu(purposeMenu->menu());
    mShareButton->setIcon(QIcon::fromTheme(QStringLiteral("document-share")));
    purposeMenu->setEditorWidget(mLogWidget->editor());
    buttonBox->addButton(mShareButton, QDialogButtonBox::ActionRole);
    mShareButton->setEnabled(false);

    connect(mSaveButton, &QPushButton::clicked, this, &LogActivitiesDialog::slotSave);

    mainLayout->addWidget(buttonBox);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &LogActivitiesDialog::reject);
    readConfig();

    connect(PimCommon::LogActivitiesManager::self(), &LogActivitiesManager::logEntryAdded, this, &LogActivitiesDialog::slotLogEntryAdded);
    connect(PimCommon::LogActivitiesManager::self(), &LogActivitiesManager::logEntryCleared, this, &LogActivitiesDialog::slotLogEntryCleared);
    connect(mLogWidget, &LogActivitiesWidget::textChanged, this, &LogActivitiesDialog::slotActivityTextChanged);
    mEnableLogActivities->setChecked(PimCommon::LogActivitiesManager::self()->enableLogActivities());
}

LogActivitiesDialog::~LogActivitiesDialog()
{
    disconnect(mLogWidget, &LogActivitiesWidget::textChanged, this, &LogActivitiesDialog::slotActivityTextChanged);
    writeConfig();
}

void LogActivitiesDialog::slotActivityTextChanged(bool changed)
{
    mSaveButton->setEnabled(changed);
    mShareButton->setEnabled(changed);
}

void LogActivitiesDialog::slotSave()
{
    const QString filter = i18n("All Files (*)");
    PimCommon::Util::saveTextAs(PimCommon::LogActivitiesManager::self()->log(), filter, this, QUrl(),
                                i18nc("@title:window", "Save Log"));
}

void LogActivitiesDialog::slotEnableLogActivities(bool state)
{
    PimCommon::LogActivitiesManager::self()->setEnableLogActivities(state);
}

void LogActivitiesDialog::setLog(const QString &str)
{
    mLogWidget->setLog(str);
}

void LogActivitiesDialog::slotLogEntryAdded(const QString &entry)
{
    mLogWidget->addLogEntry(entry);
}

void LogActivitiesDialog::slotLogEntryCleared()
{
    mLogWidget->clear();
}

void LogActivitiesDialog::slotClear()
{
    mLogWidget->clear();
    Q_EMIT logCleared();
}

void LogActivitiesDialog::readConfig()
{
    KConfigGroup group(KSharedConfig::openConfig(), "LogActivitiesDialog");
    const QSize sizeDialog = group.readEntry("Size", QSize(800, 600));
    if (sizeDialog.isValid()) {
        resize(sizeDialog);
    }
}

void LogActivitiesDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openConfig(), "LogActivitiesDialog");
    group.writeEntry("Size", size());
}
