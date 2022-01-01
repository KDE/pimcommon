/*
  SPDX-FileCopyrightText: 2015-2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#pragma once

#include "pimcommonakonadi_private_export.h"
#include <QWidget>
class QPushButton;
class QLineEdit;
class QLabel;
class KListWidgetSearchLine;
namespace PimCommon
{
class BlackListBalooEmailList;
class BlackListBalooEmailWarning;
class PIMCOMMONAKONADI_TESTS_EXPORT BlackListBalooEmailCompletionWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BlackListBalooEmailCompletionWidget(QWidget *parent = nullptr);
    ~BlackListBalooEmailCompletionWidget() override;

    void save();
    void load();
    void setEmailBlackList(const QStringList &list);

private:
    void slotSelectionChanged();
    void slotUnselectEmails();
    void slotSelectEmails();
    void slotSearchLineEditChanged(const QString &text);
    void slotSearch();
    void slotLinkClicked(const QString &link);
    void slotEmailFound(const QStringList &list);
    void slotCheckIfUpdateBlackListIsNeeded();
    void slotSaveChanges();
    void slotShowAllBlacklistedEmail();
    void hideMoreResultAndChangeLimit();
    QStringList mOriginalExcludeDomain;
    QLabel *mNumberOfEmailsFound = nullptr;
    QLineEdit *mSearchLineEdit = nullptr;
    QLineEdit *mExcludeDomainLineEdit = nullptr;
    BlackListBalooEmailList *mEmailList = nullptr;
    QPushButton *mSearchButton = nullptr;
    QPushButton *mSelectButton = nullptr;
    QPushButton *mUnselectButton = nullptr;
    QPushButton *mShowAllBlackListedEmails = nullptr;
    QLabel *mMoreResult = nullptr;
    KListWidgetSearchLine *mSearchInResultLineEdit = nullptr;
    BlackListBalooEmailWarning *mBlackListWarning = nullptr;
    int mLimit = 500;
};
}

