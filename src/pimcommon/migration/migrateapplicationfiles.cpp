/*
  SPDX-FileCopyrightText: 2015-2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "migrateapplicationfiles.h"
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
#include "pimcommon_debug.h"

#include <KConfigGroup>
#include <KSharedConfig>
#include <Kdelibs4Migration>
#include <QDir>
#include <QFile>
#include <QFileInfo>

using namespace PimCommon;

class PimCommon::MigrateApplicationFilesPrivate
{
public:
    QVector<MigrateFileInfo> mMigrateInfoList;
    QString mConfigFileName;
    QString mApplicationName;
    Kdelibs4Migration mMigration;
    int mMigrateApplicationVersion = 1;
    int mCurrentConfigVersion = 0;
};

MigrateApplicationFiles::MigrateApplicationFiles(QObject *parent)
    : QObject(parent)
    , d(new PimCommon::MigrateApplicationFilesPrivate)
{
}

MigrateApplicationFiles::~MigrateApplicationFiles() = default;

void MigrateApplicationFiles::finished()
{
    writeConfig();
    Q_EMIT migrateDone();
}

bool MigrateApplicationFiles::start()
{
    if (d->mApplicationName.isEmpty()) {
        qCDebug(PIMCOMMON_LOG) << "Missing application name";
    }
    // Testing for kdehome
    if (!d->mMigration.kdeHomeFound()) {
        finished();
        return false;
    }

    if (d->mMigrateInfoList.isEmpty()) {
        finished();
        return false;
    }

    if (d->mConfigFileName.isEmpty()) {
        qCDebug(PIMCOMMON_LOG) << " config file name not defined.";
        finished();
        return false;
    }
    return migrateConfig();
}

bool MigrateApplicationFiles::migrateConfig()
{
    qCDebug(PIMCOMMON_LOG) << "Start migration...";
    for (const MigrateFileInfo &info : std::as_const(d->mMigrateInfoList)) {
        if ((info.version() == -1) || (info.version() > d->mCurrentConfigVersion)) {
            if (info.folder()) {
                migrateFolder(info);
            } else {
                migrateFile(info);
            }
        }
    }
    qCDebug(PIMCOMMON_LOG) << "Migration finished.";
    finished();
    return true;
}

QString MigrateApplicationFiles::applicationName() const
{
    return d->mApplicationName;
}

void MigrateApplicationFiles::setApplicationName(const QString &applicationName)
{
    d->mApplicationName = applicationName;
}

int MigrateApplicationFiles::currentConfigVersion() const
{
    return d->mCurrentConfigVersion;
}

void MigrateApplicationFiles::setCurrentConfigVersion(int currentConfigVersion)
{
    d->mCurrentConfigVersion = currentConfigVersion;
}

QString MigrateApplicationFiles::configFileName() const
{
    return d->mConfigFileName;
}

void MigrateApplicationFiles::setConfigFileName(const QString &configFileName)
{
    d->mConfigFileName = configFileName;
}

void MigrateApplicationFiles::writeConfig()
{
    KSharedConfig::Ptr config = KSharedConfig::openConfig(d->mConfigFileName, KConfig::SimpleConfig);
    KConfigGroup grp = config->group(QStringLiteral("Migratekde4"));
    grp.writeEntry(QStringLiteral("Version"), d->mMigrateApplicationVersion);
    grp.sync();
}

void MigrateApplicationFiles::migrateFolder(const MigrateFileInfo &info)
{
    QString originalPath;
    QString newPath;
    if (info.type() == QLatin1String("data")) {
        originalPath = d->mMigration.locateLocal("data", info.path());
        newPath = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation) + QLatin1Char('/') + info.path();
        QFileInfo fileInfo(newPath);
        QDir().mkpath(fileInfo.absolutePath());
    } else {
        qCDebug(PIMCOMMON_LOG) << "Type not supported: " << info.type();
    }
    if (!originalPath.isEmpty()) {
        copyRecursively(originalPath, newPath);
    }
}

bool MigrateApplicationFiles::copyRecursively(const QString &srcFilePath, const QString &tgtFilePath)
{
    QFileInfo srcFileInfo(srcFilePath);
    if (srcFileInfo.isDir()) {
        QDir targetDir(tgtFilePath);
        targetDir.cdUp();
        if (!targetDir.mkpath(QFileInfo(tgtFilePath).path())) {
            return false;
        }
        QDir sourceDir(srcFilePath);
        const QStringList fileNames = sourceDir.entryList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
        for (const QString &fileName : fileNames) {
            const QString newSrcFilePath = srcFilePath + QLatin1Char('/') + fileName;
            const QString newTgtFilePath = tgtFilePath + QLatin1Char('/') + fileName;
            if (!copyRecursively(newSrcFilePath, newTgtFilePath)) {
                return false;
            }
        }
    } else {
        if (!QDir().mkpath(QFileInfo(tgtFilePath).absolutePath())) {
            qCDebug(PIMCOMMON_LOG) << "Can not create path " << srcFileInfo.absolutePath();
            return false;
        }
        if (!QFileInfo::exists(tgtFilePath) && !QFile::copy(srcFilePath, tgtFilePath)) {
            qCDebug(PIMCOMMON_LOG) << " can't copy" << srcFilePath << " tgtFilePath" << tgtFilePath;
            return false;
        }
    }
    return true;
}

void MigrateApplicationFiles::migrateFile(const MigrateFileInfo &info)
{
    QString originalPath;
    QString newPath;
    if (info.type() == QLatin1String("data")) {
        originalPath = d->mMigration.locateLocal("data", info.path());
        newPath = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation) + QLatin1Char('/') + info.path();
        QFileInfo fileInfo(newPath);
        QDir().mkpath(fileInfo.absolutePath());
    } else {
        qCDebug(PIMCOMMON_LOG) << "Type not supported: " << info.type();
    }

    if (!originalPath.isEmpty()) {
        if (info.filePatterns().isEmpty()) {
            if (!QFileInfo::exists(newPath)) {
                QFile copyFile(originalPath);
                if (!copyFile.copy(newPath)) {
                    qCDebug(PIMCOMMON_LOG) << "impossible to copy " << originalPath << " to " << newPath;
                }
            }
        } else {
            QDir sourceDir(originalPath);
            const QStringList fileNames = sourceDir.entryList(info.filePatterns(), QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
            for (const QString &file : fileNames) {
                QFile copyFile(originalPath + QLatin1Char('/') + file);
                if (!copyFile.copy(newPath + QLatin1Char('/') + file)) {
                    qCDebug(PIMCOMMON_LOG) << "impossible to copy " << copyFile.fileName() << " to " << newPath;
                }
            }
        }
    }
}

int MigrateApplicationFiles::version() const
{
    return d->mMigrateApplicationVersion;
}

void MigrateApplicationFiles::setVersion(int version)
{
    d->mMigrateApplicationVersion = version;
}

bool MigrateApplicationFiles::checkIfNecessary()
{
    if (d->mConfigFileName.isEmpty()) {
        qCDebug(PIMCOMMON_LOG) << " config file name not defined.";
        return false;
    }
    KSharedConfig::Ptr config = KSharedConfig::openConfig(d->mConfigFileName, KConfig::SimpleConfig);
    if (config->hasGroup(QStringLiteral("Migratekde4"))) {
        KConfigGroup grp = config->group(QStringLiteral("Migratekde4"));
        d->mCurrentConfigVersion = grp.readEntry(QStringLiteral("Version"), 0);
        if (d->mCurrentConfigVersion < d->mMigrateApplicationVersion) {
            return true;
        } else {
            return false;
        }
    }
    return true;
}

void MigrateApplicationFiles::insertMigrateInfo(const MigrateFileInfo &info)
{
    if (info.isValid()) {
        d->mMigrateInfoList.append(info);
    }
}
#endif
