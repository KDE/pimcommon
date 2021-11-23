/*
  SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "logactivitiesdialogtest.h"
#include "../logactivitiesdialog.h"
#include "../logactivitiesmanager.h"
#include "../logactivitieswidget.h"
#include <QAbstractButton>
#include <QCheckBox>
#include <QDialogButtonBox>
#include <QSignalSpy>
#include <QStandardPaths>
#include <QTest>
#include <QVBoxLayout>
#include <qtestmouse.h>

LogActivitiesDialogTest::LogActivitiesDialogTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

LogActivitiesDialogTest::~LogActivitiesDialogTest() = default;

void LogActivitiesDialogTest::shouldHaveDefaultValue()
{
    PimCommon::LogActivitiesDialog w;
    auto mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);

    auto mLogWidget = w.findChild<PimCommon::LogActivitiesWidget *>(QStringLiteral("logwidget"));
    QVERIFY(mLogWidget);

    auto mEnableLogActivities = w.findChild<QCheckBox *>(QStringLiteral("enablelogactivities"));
    QVERIFY(mEnableLogActivities);
    QVERIFY(!mEnableLogActivities->text().isEmpty());
    QVERIFY(!mEnableLogActivities->isChecked());

    auto buttonBox = w.findChild<QDialogButtonBox *>(QStringLiteral("buttonbox"));
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
    auto buttonBox = w.findChild<QDialogButtonBox *>(QStringLiteral("buttonbox"));

    auto mLogWidget = w.findChild<PimCommon::LogActivitiesWidget *>(QStringLiteral("logwidget"));

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
    auto mEnableLogActivities = w.findChild<QCheckBox *>(QStringLiteral("enablelogactivities"));
    QVERIFY(mEnableLogActivities->isChecked());
}

QTEST_MAIN(LogActivitiesDialogTest)
