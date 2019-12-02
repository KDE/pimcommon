/*
  Copyright (c) 2015-2019 Montel Laurent <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef MIGRATEAPPLICATIONFILE_H
#define MIGRATEAPPLICATIONFILE_H

#include <QObject>
#include <Kdelibs4Migration>
#include "migratefileinfo.h"
#include "pimcommon_export.h"
namespace PimCommon {
class MigrateApplicationFilesPrivate;
/**
 * @brief The MigrateApplicationFiles class
 * @author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT MigrateApplicationFiles : public QObject
{
    Q_OBJECT
public:
    explicit MigrateApplicationFiles(QObject *parent = nullptr);
    ~MigrateApplicationFiles();

    Q_REQUIRED_RESULT bool start();
    Q_REQUIRED_RESULT bool checkIfNecessary();
    void insertMigrateInfo(const MigrateFileInfo &info);

    Q_REQUIRED_RESULT int version() const;
    void setVersion(int version);

    Q_REQUIRED_RESULT QString configFileName() const;
    void setConfigFileName(const QString &configFileName);

    Q_REQUIRED_RESULT int currentConfigVersion() const;
    void setCurrentConfigVersion(int currentConfigVersion);

    Q_REQUIRED_RESULT QString applicationName() const;
    void setApplicationName(const QString &applicationName);

Q_SIGNALS:
    void migrateDone();

private:
    bool copyRecursively(const QString &srcFilePath, const QString &tgtFilePath);
    void finished();
    void writeConfig();
    void migrateFolder(const MigrateFileInfo &info);
    void migrateFile(const MigrateFileInfo &info);
    bool migrateConfig();
    MigrateApplicationFilesPrivate *const d;
};
}
#endif // MIGRATEAPPLICATIONFILE_H
