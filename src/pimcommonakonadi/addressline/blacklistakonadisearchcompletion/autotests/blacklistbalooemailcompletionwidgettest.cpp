/*
  SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "blacklistbalooemailcompletionwidgettest.h"
#include "../blacklistakonadisearchemailcompletionwidget.h"
#include "../blacklistakonadisearchemaillist.h"
#include "addressline/blacklistakonadisearchcompletion/blacklistakonadisearchemailwarning.h"
#include <KListWidgetSearchLine>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTest>

BlackListBalooEmailCompletionWidgetTest::BlackListBalooEmailCompletionWidgetTest(QObject *parent)
    : QObject(parent)
{
    if (qEnvironmentVariableIntValue("KDECI_CANNOT_CREATE_WINDOWS")) {
        QSKIP("KDE CI can't create a window on this platform, skipping some gui tests");
    }
}

BlackListBalooEmailCompletionWidgetTest::~BlackListBalooEmailCompletionWidgetTest() = default;

void BlackListBalooEmailCompletionWidgetTest::shouldHaveDefaultValue()
{
    PimCommon::BlackListAkonadiSearchEmailCompletionWidget widget;
    widget.show();
    QVERIFY(QTest::qWaitForWindowExposed(&widget));
    auto searchLabel = widget.findChild<QLabel *>(QStringLiteral("search_label"));
    QVERIFY(searchLabel);

    auto searchLineEdit = widget.findChild<QLineEdit *>(QStringLiteral("search_lineedit"));
    QVERIFY(searchLineEdit);
    QVERIFY(searchLineEdit->isClearButtonEnabled());
    QVERIFY(searchLineEdit->text().isEmpty());

    auto seachButton = widget.findChild<QPushButton *>(QStringLiteral("search_button"));
    QVERIFY(seachButton);
    QVERIFY(!seachButton->isEnabled());

    auto moreResult = widget.findChild<QLabel *>(QStringLiteral("moreresultlabel"));
    QVERIFY(moreResult);
    QVERIFY(!moreResult->isVisible());

    auto mNumberOfEmailsFound = widget.findChild<QLabel *>(QStringLiteral("numberofemailsfound"));
    QVERIFY(mNumberOfEmailsFound);
    QVERIFY(mNumberOfEmailsFound->text().isEmpty());

    auto showAllBlackListedEmails = widget.findChild<QPushButton *>(QStringLiteral("show_blacklisted_email_button"));
    QVERIFY(showAllBlackListedEmails);

    auto emailList = widget.findChild<PimCommon::BlackListAkonadiSearchEmailList *>(QStringLiteral("email_list"));
    QVERIFY(emailList);

    auto selectButton = widget.findChild<QPushButton *>(QStringLiteral("select_email"));
    QVERIFY(selectButton);
    QVERIFY(!selectButton->isEnabled());
    auto unselectButton = widget.findChild<QPushButton *>(QStringLiteral("unselect_email"));
    QVERIFY(unselectButton);
    QVERIFY(!unselectButton->isEnabled());

    auto excludeDomainLabel = widget.findChild<QLabel *>(QStringLiteral("domain_label"));
    QVERIFY(excludeDomainLabel);

    auto excludeDomainLineEdit = widget.findChild<QLineEdit *>(QStringLiteral("domain_lineedit"));
    QVERIFY(excludeDomainLineEdit);
    QVERIFY(excludeDomainLineEdit->text().isEmpty());
    QVERIFY(excludeDomainLineEdit->isClearButtonEnabled());
    QVERIFY(!excludeDomainLineEdit->placeholderText().isEmpty());

    auto searchInResult = widget.findChild<KListWidgetSearchLine *>(QStringLiteral("searchinresultlineedit"));
    QVERIFY(searchInResult);
    QVERIFY(!searchInResult->placeholderText().isEmpty());
    QVERIFY(searchInResult->text().isEmpty());
    QVERIFY(searchInResult->isClearButtonEnabled());

    auto blackListWarning = widget.findChild<PimCommon::BlackListAkonadiSearchEmailWarning *>(QStringLiteral("backlistwarning"));
    QVERIFY(blackListWarning);
}

void BlackListBalooEmailCompletionWidgetTest::shouldEnablePushButtonWhenTestSizeSupperiorToTwo()
{
    PimCommon::BlackListAkonadiSearchEmailCompletionWidget widget;
    auto searchLineEdit = widget.findChild<QLineEdit *>(QStringLiteral("search_lineedit"));
    auto seachButton = widget.findChild<QPushButton *>(QStringLiteral("search_button"));
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
    PimCommon::BlackListAkonadiSearchEmailCompletionWidget widget;

    auto selectButton = widget.findChild<QPushButton *>(QStringLiteral("select_email"));
    QVERIFY(!selectButton->isEnabled());

    auto unselectButton = widget.findChild<QPushButton *>(QStringLiteral("unselect_email"));
    QVERIFY(!unselectButton->isEnabled());

    auto emailList = widget.findChild<PimCommon::BlackListAkonadiSearchEmailList *>(QStringLiteral("email_list"));
    QVERIFY((emailList->setEmailFound(QStringList() << QStringLiteral("foo") << QStringLiteral("bla") << QStringLiteral("bli")) > 0));

    emailList->selectAll();
    QVERIFY(unselectButton->isEnabled());
    QVERIFY(selectButton->isEnabled());

    emailList->clearSelection();
    QVERIFY(!unselectButton->isEnabled());
    QVERIFY(!selectButton->isEnabled());
}

QTEST_MAIN(BlackListBalooEmailCompletionWidgetTest)

#include "moc_blacklistbalooemailcompletionwidgettest.cpp"
