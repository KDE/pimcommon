/*
  Copyright (c) 2017 Montel Laurent <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License, version 2, as
  published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "logactivitiesdialogtest.h"
#include "../logactivitiesdialog.h"
#include "../logactivitieswidget.h"
#include "../logactivitiesmanager.h"
#include <QAbstractButton>
#include <QDialogButtonBox>
#include <QTest>
#include <QVBoxLayout>
#include <qtestmouse.h>
#include <QSignalSpy>
#include <QCheckBox>
#include <QStandardPaths>

LogActivitiesDialogTest::LogActivitiesDialogTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

LogActivitiesDialogTest::~LogActivitiesDialogTest()
{

}

void LogActivitiesDialogTest::shouldHaveDefaultValue()
{
    PimCommon::LogActivitiesDialog w;
    QVBoxLayout *mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);

    PimCommon::LogActivitiesWidget *mLogWidget = w.findChild<PimCommon::LogActivitiesWidget *>(QStringLiteral("logwidget"));
    QVERIFY(mLogWidget);

    QCheckBox *mEnableLogActivities = w.findChild<QCheckBox *>(QStringLiteral("enablelogactivities"));
    QVERIFY(mEnableLogActivities);
    QVERIFY(!mEnableLogActivities->text().isEmpty());
    QVERIFY(!mEnableLogActivities->isChecked());

    QDialogButtonBox *buttonBox = w.findChild<QDialogButtonBox *>(QStringLiteral("buttonbox"));
    QVERIFY(buttonBox);

    const QList<QAbstractButton *> lstButtonBox = buttonBox->buttons();
    bool hasClearButton = false;
    for (QAbstractButton *b : lstButtonBox) {
        if (b->objectName() == QLatin1String("clearbutton")) {
            hasClearButton = true;
            QVERIFY(!b->text().isEmpty());
        } else if (b->objectName() == QLatin1String("savebutton")) {
            QVERIFY(!b->isEnabled());
        }
    }
    QVERIFY(hasClearButton);
}

void LogActivitiesDialogTest::shouldClearLog()
{
    PimCommon::LogActivitiesDialog w;
    QDialogButtonBox *buttonBox = w.findChild<QDialogButtonBox *>(QStringLiteral("buttonbox"));

    PimCommon::LogActivitiesWidget *mLogWidget = w.findChild<PimCommon::LogActivitiesWidget *>(QStringLiteral("logwidget"));

    QVERIFY(mLogWidget->log().isEmpty());

    mLogWidget->setLog(QStringLiteral("FOOO"));
    QVERIFY(!mLogWidget->log().isEmpty());

    const QList<QAbstractButton *> lstButtonBox = buttonBox->buttons();
    QAbstractButton *clearButton = nullptr;
    for (QAbstractButton *b : lstButtonBox) {
        if (b->objectName() == QLatin1String("clearbutton")) {
            clearButton = b;
            break;
        }
    }
    QSignalSpy spy(&w, &PimCommon::LogActivitiesDialog::logCleared);
    QTest::mouseClick(clearButton, Qt::LeftButton);
    QCOMPARE(spy.count(), 1);
    QVERIFY(mLogWidget->log().isEmpty());
}

void LogActivitiesDialogTest::shouldHaveCorrectLogActivities()
{
    PimCommon::LogActivitiesManager::self()->setEnableLogActivities(true);
    PimCommon::LogActivitiesDialog w;
    QCheckBox *mEnableLogActivities = w.findChild<QCheckBox *>(QStringLiteral("enablelogactivities"));
    QVERIFY(mEnableLogActivities->isChecked());
}

QTEST_MAIN(LogActivitiesDialogTest)
