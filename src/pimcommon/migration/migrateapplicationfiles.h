/*
  SPDX-FileCopyrightText: 2015-2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "migratefileinfo.h"
#include "pimcommon_export.h"
#include <QObject>
#include <memory>
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
namespace PimCommon
{
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
    ~MigrateApplicationFiles() override;

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
    std::unique_ptr<MigrateApplicationFilesPrivate> const d;
};
}
#endif
