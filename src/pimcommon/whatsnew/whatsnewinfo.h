/*
   SPDX-FileCopyrightText: 2024 Laurent Montel <montel.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once
#include "pimcommon_export.h"
#include <QDebug>
#include <QStringList>
namespace PimCommon
{
class PIMCOMMON_EXPORT WhatsNewInfo
{
public:
    WhatsNewInfo();
    ~WhatsNewInfo();

    [[nodiscard]] QStringList changes() const;
    void setChanges(const QStringList &newChanges);

    [[nodiscard]] QStringList newFeatures() const;
    void setNewFeatures(const QStringList &newNewFeatures);

    [[nodiscard]] QStringList bugFixings() const;
    void setBugFixings(const QStringList &newBugFixings);

    [[nodiscard]] QString version() const;
    void setVersion(const QString &newVersion);

private:
    QString mVersion;
    QStringList mChanges;
    QStringList mNewFeatures;
    QStringList mBugFixings;
};
}
Q_DECLARE_METATYPE(PimCommon::WhatsNewInfo)
Q_DECLARE_TYPEINFO(PimCommon::WhatsNewInfo, Q_RELOCATABLE_TYPE);
PIMCOMMON_EXPORT QDebug operator<<(QDebug d, const PimCommon::WhatsNewInfo &t);
