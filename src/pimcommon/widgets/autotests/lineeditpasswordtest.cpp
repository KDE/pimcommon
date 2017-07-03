/*
  Copyright (c) 2017 Montel Laurent <montel@kde.org>

  based on lineedit in kpassworddialog.cpp

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

#include "lineeditpasswordtest.h"
#include "../lineeditpassword.h"
#include <QHBoxLayout>
#include <QLineEdit>
#include <QTest>
#include <QAction>

LineEditPasswordTest::LineEditPasswordTest(QObject *parent)
    : QObject(parent)
{

}

void LineEditPasswordTest::shouldHaveDefaultValue()
{
    PimCommon::LineEditPassword lineEdit;
    QVERIFY(lineEdit.password().isEmpty());

    QHBoxLayout *mainLayout = lineEdit.findChild<QHBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->margin(), 0);

    QLineEdit *edit = lineEdit.findChild<QLineEdit *>(QStringLiteral("passwordlineedit"));
    QVERIFY(edit);
    QVERIFY(edit->text().isEmpty());
    QCOMPARE(edit->echoMode(), QLineEdit::Password);

    QVERIFY(lineEdit.toggleEchoModeAction());
    QVERIFY(!lineEdit.toggleEchoModeAction()->isVisible());
}

void LineEditPasswordTest::shouldShowTogglePassword()
{
    PimCommon::LineEditPassword lineEdit;
    lineEdit.show();
    QTest::qWaitForWindowExposed(&lineEdit);

    QLineEdit *edit = lineEdit.findChild<QLineEdit *>(QStringLiteral("passwordlineedit"));
    edit->setText(QStringLiteral("FOO"));
    QVERIFY(lineEdit.toggleEchoModeAction()->isVisible());

    edit->clear();
    QVERIFY(!lineEdit.toggleEchoModeAction()->isVisible());
}

void LineEditPasswordTest::shouldNotShowToggleWhenSetPassword()
{
    PimCommon::LineEditPassword lineEdit;
    lineEdit.show();
    QTest::qWaitForWindowExposed(&lineEdit);
    lineEdit.setPassword(QStringLiteral("foo"));
    QVERIFY(!lineEdit.toggleEchoModeAction()->isVisible());
}

QTEST_MAIN(LineEditPasswordTest)
