/*
  SPDX-FileCopyrightText: 2015-2024 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#pragma once

#include "pimcommonakonadi_private_export.h"
#include <QHash>
#include <QListWidget>
#include <QListWidgetItem>

namespace PimCommon
{
class PIMCOMMONAKONADI_TESTS_EXPORT BlackListBalooEmailListItem : public QListWidgetItem
{
public:
    explicit BlackListBalooEmailListItem(QListWidget *parent = nullptr);
    ~BlackListBalooEmailListItem() override;

    [[nodiscard]] bool initializeStatus() const;
    void setInitializeStatus(bool initializeStatus);

private:
    bool mInitializeStatus;
};

class PIMCOMMONAKONADI_TESTS_EXPORT BlackListBalooEmailList : public QListWidget
{
    Q_OBJECT
public:
    explicit BlackListBalooEmailList(QWidget *parent = nullptr);
    ~BlackListBalooEmailList() override;

    void setEmailBlackList(const QStringList &list);

    [[nodiscard]] QHash<QString, bool> blackListItemChanged() const;

    void setExcludeDomains(const QStringList &domain);
    [[nodiscard]] int setEmailFound(const QStringList &);

    void setExcludeEmailsRegularExpressions(const QStringList &newExcludeEmailsRegularExpressions);

protected:
    void paintEvent(QPaintEvent *event) override;

    void changeEvent(QEvent *event) override;

private:
    void generalPaletteChanged();
    QStringList mExcludeEmailsRegularExpressions;
    QStringList mEmailBlackList;
    QStringList mExcludeDomains;
    QColor mTextColor;
    bool mFirstResult = false;
};
}
