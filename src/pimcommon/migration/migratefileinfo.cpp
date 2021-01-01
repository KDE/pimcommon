/*
  SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "migratefileinfo.h"
using namespace PimCommon;

MigrateFileInfo::MigrateFileInfo()
{
}

bool MigrateFileInfo::isValid() const
{
    return !mType.isEmpty() && !mPath.isEmpty();
}

int MigrateFileInfo::version() const
{
    return mVersion;
}

void MigrateFileInfo::setVersion(int version)
{
    mVersion = version;
}

QString MigrateFileInfo::type() const
{
    return mType;
}

void MigrateFileInfo::setType(const QString &type)
{
    mType = type;
}

QString MigrateFileInfo::path() const
{
    return mPath;
}

void MigrateFileInfo::setPath(const QString &path)
{
    mPath = path;
}

bool MigrateFileInfo::folder() const
{
    return mFolder;
}

void MigrateFileInfo::setFolder(bool folder)
{
    mFolder = folder;
}

QStringList MigrateFileInfo::filePatterns() const
{
    return mFilePattern;
}

void MigrateFileInfo::setFilePatterns(const QStringList &filePattern)
{
    mFilePattern = filePattern;
}
