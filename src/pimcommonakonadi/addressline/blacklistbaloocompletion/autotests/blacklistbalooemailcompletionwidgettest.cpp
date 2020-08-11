/*
  SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "blacklistbalooemailcompletionwidgettest.h"
#include "../blacklistbalooemailcompletionwidget.h"
#include "../blacklistbalooemaillist.h"
#include <KListWidgetSearchLine>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTest>
#include <addressline/blacklistbaloocompletion/blacklistbalooemailwarning.h>

BlackListBalooEmailCompletionWidgetTest::BlackListBalooEmailCompletionWidgetTest(QObject *parent)
    : QObject(parent)
{
}

BlackListBalooEmailCompletionWidgetTest::~BlackListBalooEmailCompletionWidgetTest()
{
}

void BlackListBalooEmailCompletionWidgetTest::shouldHaveDefaultValue()
{
    PimCommon::BlackListBalooEmailCompletionWidget widget;
    widget.show();
    QVERIFY(QTest::qWaitForWindowExposed(&widget));
    QLabel *searchLabel = widget.findChild<QLabel *>(QStringLiteral("search_label"));
    QVERIFY(searchLabel);

    QLineEdit *searchLineEdit = widget.findChild<QLineEdit *>(QStringLiteral("search_lineedit"));
    QVERIFY(searchLineEdit);
    QVERIFY(searchLineEdit->isClearButtonEnabled());
    QVERIFY(searchLineEdit->text().isEmpty());

    QPushButton *seachButton = widget.findChild<QPushButton *>(QStringLiteral("search_button"));
    QVERIFY(seachButton);
    QVERIFY(!seachButton->isEnabled());

    QLabel *moreResult = widget.findChild<QLabel *>(QStringLiteral("moreresultlabel"));
    QVERIFY(moreResult);
    QVERIFY(!moreResult->isVisible());

    QLabel *mNumberOfEmailsFound = widget.findChild<QLabel *>(QStringLiteral("numberofemailsfound"));
    QVERIFY(mNumberOfEmailsFound);
    QVERIFY(mNumberOfEmailsFound->text().isEmpty());

    QPushButton *showAllBlackListedEmails = widget.findChild<QPushButton *>(QStringLiteral("show_blacklisted_email_button"));
    QVERIFY(showAllBlackListedEmails);

    PimCommon::BlackListBalooEmailList *emailList = widget.findChild<PimCommon::BlackListBalooEmailList *>(QStringLiteral("email_list"));
    QVERIFY(emailList);

    QPushButton *selectButton = widget.findChild<QPushButton *>(QStringLiteral("select_email"));
    QVERIFY(selectButton);
    QVERIFY(!selectButton->isEnabled());
    QPushButton *unselectButton = widget.findChild<QPushButton *>(QStringLiteral("unselect_email"));
    QVERIFY(unselectButton);
    QVERIFY(!unselectButton->isEnabled());

    QLabel *excludeDomainLabel = widget.findChild<QLabel *>(QStringLiteral("domain_label"));
    QVERIFY(excludeDomainLabel);

    QLineEdit *excludeDomainLineEdit = widget.findChild<QLineEdit *>(QStringLiteral("domain_lineedit"));
    QVERIFY(excludeDomainLineEdit);
    QVERIFY(excludeDomainLineEdit->text().isEmpty());
    QVERIFY(excludeDomainLineEdit->isClearButtonEnabled());
    QVERIFY(!excludeDomainLineEdit->placeholderText().isEmpty());

    KListWidgetSearchLine *searchInResult = widget.findChild<KListWidgetSearchLine *>(QStringLiteral("searchinresultlineedit"));
    QVERIFY(searchInResult);
    QVERIFY(!searchInResult->placeholderText().isEmpty());
    QVERIFY(searchInResult->text().isEmpty());
    QVERIFY(searchInResult->isClearButtonEnabled());

    PimCommon::BlackListBalooEmailWarning *blackListWarning = widget.findChild<PimCommon::BlackListBalooEmailWarning *>(QStringLiteral("backlistwarning"));
    QVERIFY(blackListWarning);
}

void BlackListBalooEmailCompletionWidgetTest::shouldEnablePushButtonWhenTestSizeSupperiorToTwo()
{
    PimCommon::BlackListBalooEmailCompletionWidget widget;
    QLineEdit *searchLineEdit = widget.findChild<QLineEdit *>(QStringLiteral("search_lineedit"));
    QPushButton *seachButton = widget.findChild<QPushButton *>(QStringLiteral("search_button"));
    QVERIFY(!seachButton->isEnabled());
    searchLineEdit->setText(QStringLiteral("fo"));
    QVERIFY(!seachButton->isEnabled());
    searchLineEdit->setText(QStringLiteral("foo"));
    QVERIFY(seachButton->isEnabled());

    searchLineEdit->setText(QStringLiteral("o  "));
    QVERIFY(!seachButton->isEnabled());
    searchLineEdit->setText(QStringLiteral(" o "));
    QVERIFY(!seachButton->isEnabled());
}

void BlackListBalooEmailCompletionWidgetTest::shouldChangeEnableSelectUnSelectButton()
{
    PimCommon::BlackListBalooEmailCompletionWidget widget;

    QPushButton *selectButton = widget.findChild<QPushButton *>(QStringLiteral("select_email"));
    QVERIFY(!selectButton->isEnabled());

    QPushButton *unselectButton = widget.findChild<QPushButton *>(QStringLiteral("unselect_email"));
    QVERIFY(!unselectButton->isEnabled());

    PimCommon::BlackListBalooEmailList *emailList = widget.findChild<PimCommon::BlackListBalooEmailList *>(QStringLiteral("email_list"));
    QVERIFY((emailList->setEmailFound(QStringList() << QStringLiteral("foo") << QStringLiteral("bla") << QStringLiteral("bli")) > 0));

    emailList->selectAll();
    QVERIFY(unselectButton->isEnabled());
    QVERIFY(selectButton->isEnabled());

    emailList->clearSelection();
    QVERIFY(!unselectButton->isEnabled());
    QVERIFY(!selectButton->isEnabled());
}

QTEST_MAIN(BlackListBalooEmailCompletionWidgetTest)
