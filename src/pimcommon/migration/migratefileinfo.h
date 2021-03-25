/*
  SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QString>
#include <QStringList>

#include "pimcommon_export.h"
namespace PimCommon
{
/**
 * @brief The MigrateFileInfo class
 * @author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT MigrateFileInfo
{
public:
    MigrateFileInfo();

    Q_REQUIRED_RESULT QString type() const;
    void setType(const QString &type);

    Q_REQUIRED_RESULT QString path() const;
    void setPath(const QString &path);

    Q_REQUIRED_RESULT bool folder() const;
    void setFolder(bool folder);

    Q_REQUIRED_RESULT bool isValid() const;

    Q_REQUIRED_RESULT int version() const;
    void setVersion(int version);

    Q_REQUIRED_RESULT QStringList filePatterns() const;
    void setFilePatterns(const QStringList &filePatterns);

private:
    QStringList mFilePattern;
    QString mType;
    QString mPath;
    int mVersion = -1;
    bool mFolder = false;
};
}

