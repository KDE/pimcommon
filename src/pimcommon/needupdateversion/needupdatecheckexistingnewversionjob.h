/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "pimcommon_export.h"
#include <QDate>
#include <QObject>
#include <QUrl>
namespace PimCommon
{
class PIMCOMMON_EXPORT NeedUpdateCheckExistingNewVersionJob : public QObject
{
    Q_OBJECT
public:
    explicit NeedUpdateCheckExistingNewVersionJob(QObject *parent = nullptr);
    ~NeedUpdateCheckExistingNewVersionJob() override;

    void start();

    [[nodiscard]] QUrl url() const;
    void setUrl(const QUrl &newUrl);

    [[nodiscard]] bool canStart() const;

    [[nodiscard]] QDate compileDate() const;
    void setCompileDate(const QDate &newCompileDate);

Q_SIGNALS:
    void foundNewVersion(bool state);

private:
    PIMCOMMON_NO_EXPORT void slotDownloadDone(const QString &str);
    QUrl mUrl;
    QDate mCompileDate;
};
}