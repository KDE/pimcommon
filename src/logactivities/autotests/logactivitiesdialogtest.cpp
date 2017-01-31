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
#include <QDialogButtonBox>
#include <QTest>
#include <QVBoxLayout>

LogActivitiesDialogTest::LogActivitiesDialogTest(QObject *parent)
    : QObject(parent)
{

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

    QDialogButtonBox *buttonBox = w.findChild<QDialogButtonBox *>(QStringLiteral("buttonbox"));
    QVERIFY(buttonBox);
}

QTEST_MAIN(LogActivitiesDialogTest)
