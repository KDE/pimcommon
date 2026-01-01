/*
  SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#pragma once

#include <QObject>

#include "pimcommonakonadi_private_export.h"
namespace PimCommon
{
class PIMCOMMONAKONADI_TESTS_EXPORT BlackListAkonadiSearchEmailSearchJob : public QObject
{
    Q_OBJECT
public:
    explicit BlackListAkonadiSearchEmailSearchJob(QObject *parent = nullptr);
    ~BlackListAkonadiSearchEmailSearchJob() override;

    [[nodiscard]] bool start();

    void setSearchEmail(const QString &searchEmail);

    void setLimit(int limit);

Q_SIGNALS:
    void emailsFound(const QStringList &list);

private:
    QString mSearchEmail;
    int mLimit = 500;
};
}
