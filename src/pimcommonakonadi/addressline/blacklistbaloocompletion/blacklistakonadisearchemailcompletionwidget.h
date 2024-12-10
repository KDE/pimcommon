/*
  SPDX-FileCopyrightText: 2015-2024 Laurent Montel <montel@kde.org>

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
class BlackListAkonadiSearchEmailList;
class BlackListAkonadiSearchEmailWarning;
class PIMCOMMONAKONADI_TESTS_EXPORT BlackListAkonadiSearchEmailCompletionWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BlackListAkonadiSearchEmailCompletionWidget(QWidget *parent = nullptr);
    ~BlackListAkonadiSearchEmailCompletionWidget() override;

    void save();
    void load();
    void setEmailBlackList(const QStringList &list);

private:
    PIMCOMMONAKONADI_NO_EXPORT void slotSelectionChanged();
    PIMCOMMONAKONADI_NO_EXPORT void slotUnselectEmails();
    PIMCOMMONAKONADI_NO_EXPORT void slotSelectEmails();
    PIMCOMMONAKONADI_NO_EXPORT void slotSearchLineEditChanged(const QString &text);
    PIMCOMMONAKONADI_NO_EXPORT void slotSearch();
    PIMCOMMONAKONADI_NO_EXPORT void slotLinkClicked(const QString &link);
    PIMCOMMONAKONADI_NO_EXPORT void slotEmailFound(const QStringList &list);
    PIMCOMMONAKONADI_NO_EXPORT void slotCheckIfUpdateBlackListIsNeeded();
    PIMCOMMONAKONADI_NO_EXPORT void slotSaveChanges();
    PIMCOMMONAKONADI_NO_EXPORT void slotShowAllBlacklistedEmail();
    PIMCOMMONAKONADI_NO_EXPORT void hideMoreResultAndChangeLimit();
    PIMCOMMONAKONADI_NO_EXPORT void slotCustomContextMenuRequested(const QPoint &pos);
    QStringList mOriginalExcludeDomain;
    QStringList mOriginalExcludeEmailRegexp;
    QLabel *const mNumberOfEmailsFound;
    QLineEdit *const mSearchLineEdit;
    QLineEdit *const mExcludeDomainLineEdit;
    BlackListAkonadiSearchEmailList *const mEmailList;
    QPushButton *const mSearchButton;
    QPushButton *const mSelectButton;
    QPushButton *const mUnselectButton;
    QPushButton *const mShowAllBlackListedEmails;
    QLabel *const mMoreResult;
    KListWidgetSearchLine *mSearchInResultLineEdit = nullptr;
    BlackListAkonadiSearchEmailWarning *const mBlackListWarning;
    QLineEdit *const mExcludeEmailFromRegularExpressionLineEdit;
    int mLimit = 500;
};
}
