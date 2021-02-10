/*
  SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#ifndef BLACKLISTBALOOEMAILLIST_H
#define BLACKLISTBALOOEMAILLIST_H

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

    Q_REQUIRED_RESULT bool initializeStatus() const;
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

    Q_REQUIRED_RESULT QHash<QString, bool> blackListItemChanged() const;

    void setExcludeDomain(const QStringList &domain);
    Q_REQUIRED_RESULT int setEmailFound(const QStringList &);

protected:
    void paintEvent(QPaintEvent *event) override;

    void changeEvent(QEvent *event) override;

private:
    void generalPaletteChanged();
    QStringList mEmailBlackList;
    QStringList mExcludeDomain;
    QColor mTextColor;
    bool mFirstResult = false;
};
}

#endif // BLACKLISTBALOOEMAILLIST_H
