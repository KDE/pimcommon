/*
  SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "migrateapplicationfilestest.h"
#include "../migrateapplicationfiles.h"
#include <QTest>
#include <QStandardPaths>
#include <QDebug>
#include <QDir>
#include <QTemporaryDir>

using namespace PimCommon;
MigrateApplicationFilesTest::MigrateApplicationFilesTest(QObject *parent)
    : QObject(parent)
{
}

MigrateApplicationFilesTest::~MigrateApplicationFilesTest()
{
}

void MigrateApplicationFilesTest::initTestCase()
{
    //qDebug() << " QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation)" <<QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation);
    QStandardPaths::setTestModeEnabled(true);
    const QString applicationHome = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation);
    //qDebug() << "application data" << applicationHome;
    QDir(applicationHome).removeRecursively();
}

void MigrateApplicationFilesTest::shouldHaveDefaultValue()
{
    MigrateApplicationFiles migrate;
    QVERIFY(!migrate.start());
    QVERIFY(migrate.configFileName().isEmpty());
    QVERIFY(migrate.applicationName().isEmpty());
}

void MigrateApplicationFilesTest::shouldVerifyIfCheckIsNecessary()
{
    MigrateApplicationFiles migrate;
    //Invalid before config file is not set.
    QVERIFY(!migrate.checkIfNecessary());
    migrate.setConfigFileName(QStringLiteral("foorc"));
    // If config file doesn't exist we need to check migrate
    QVERIFY(migrate.checkIfNecessary());
}

void MigrateApplicationFilesTest::shouldNotMigrateIfKdehomeDoNotExist()
{
    qputenv("KDEHOME", "");
    MigrateApplicationFiles migrate;
    migrate.setConfigFileName(QStringLiteral("foorc"));

    QCOMPARE(migrate.start(), false);
}

void MigrateApplicationFilesTest::shouldMigrateIfKde4HomeDirExist()
{
    QTemporaryDir kdehomeDir;
    QVERIFY(kdehomeDir.isValid());
    const QString kdehome = kdehomeDir.path();
    qputenv("KDEHOME", QFile::encodeName(kdehome));
    MigrateApplicationFiles migrate;
    QCOMPARE(migrate.start(), false);

    migrate.setConfigFileName(QStringLiteral("foorc"));

    MigrateFileInfo info;
    info.setPath(QStringLiteral("foo/foo"));
    info.setType(QStringLiteral("data"));

    migrate.insertMigrateInfo(info);
    QCOMPARE(migrate.start(), true);
}

void MigrateApplicationFilesTest::shouldMigrateFolders()
{
    QTemporaryDir kdehomeDir;
    QVERIFY(kdehomeDir.isValid());
    const QString kdehome = kdehomeDir.path();
    qputenv("KDEHOME", QFile::encodeName(kdehome));

    //Generate kde4 apps dir
    const QString folderName = QStringLiteral("foo/folder1/");
    const QString appsPath = kdehome + QLatin1Char('/') + QLatin1String("share/apps/") + folderName;
    QDir().mkpath(appsPath);
    QVERIFY(QDir(appsPath).exists());

    QStringList files;
    files << QStringLiteral("file1") << QStringLiteral("file2");
    const QString xdgDatahome = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation) + QLatin1Char('/') + folderName;
    for (const QString &file : qAsConst(files)) {
        QFile fooFile(QLatin1String(MIGRATION_DATA_DIR) + QLatin1Char('/') + file);
        QVERIFY(fooFile.exists());
        const QString storedConfigFilePath = appsPath + QLatin1Char('/') + file;
        QVERIFY(QFile::copy(fooFile.fileName(), storedConfigFilePath));

        const QString xdgFile = xdgDatahome + file;
        QVERIFY(!QFile::exists(xdgFile));
    }
    MigrateApplicationFiles migrate;
    migrate.setConfigFileName(QStringLiteral("foorc"));

    MigrateFileInfo info;
    info.setFolder(true);
    info.setPath(folderName);
    info.setType(QStringLiteral("data"));
    info.setVersion(1);
    migrate.insertMigrateInfo(info);

    QVERIFY(migrate.checkIfNecessary());

    QVERIFY(migrate.start());
    for (const QString &file : qAsConst(files)) {
        QVERIFY(QFile(xdgDatahome + file).exists());
    }
}

void MigrateApplicationFilesTest::shouldNotMigrateFoldersIfAlreadyDone()
{
    QTemporaryDir kdehomeDir;
    QVERIFY(kdehomeDir.isValid());
    const QString kdehome = kdehomeDir.path();
    qputenv("KDEHOME", QFile::encodeName(kdehome));

    //Generate kde4 apps dir
    const QString folderName = QStringLiteral("foo/folder1/");
    const QString appsPath = kdehome + QLatin1Char('/') + QLatin1String("share/apps/") + folderName;
    QDir().mkpath(appsPath);
    QVERIFY(QDir(appsPath).exists());

    QStringList files;
    files << QStringLiteral("file1") << QStringLiteral("file2");
    const QString xdgDatahome = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation) + QLatin1Char('/') + folderName;
    for (const QString &file : qAsConst(files)) {
        QFile fooFile(QLatin1String(MIGRATION_DATA_DIR) + QLatin1Char('/') + file);
        QVERIFY(fooFile.exists());
        const QString storedConfigFilePath = appsPath + QLatin1Char('/') + file;
        QVERIFY(QFile::copy(fooFile.fileName(), storedConfigFilePath));

        const QString xdgFile = xdgDatahome + file;
        QVERIFY(!QFile::exists(xdgFile));
    }
    MigrateApplicationFiles migrate;
    migrate.setConfigFileName(QStringLiteral("foorc"));
    QVERIFY(migrate.checkIfNecessary());

    //We have a current version == 2 => don't migrate old info. Put after checkIfNecessary to override value
    migrate.setCurrentConfigVersion(3);

    MigrateFileInfo info;
    info.setFolder(true);
    info.setPath(folderName);
    info.setType(QStringLiteral("data"));
    info.setVersion(2);
    migrate.insertMigrateInfo(info);

    QVERIFY(migrate.start());
    for (const QString &file : qAsConst(files)) {
        QVERIFY(!QFile(xdgDatahome + file).exists());
    }
}

void MigrateApplicationFilesTest::shouldMigrateFoldersWithSubFolders()
{
    QTemporaryDir kdehomeDir;
    QVERIFY(kdehomeDir.isValid());
    const QString kdehome = kdehomeDir.path();
    qputenv("KDEHOME", QFile::encodeName(kdehome));

    //Generate kde4 apps dir
    const QString folderName = QStringLiteral("foo/folder1/");
    const QString appsPath = kdehome + QLatin1Char('/') + QLatin1String("share/apps/") + folderName;
    QDir().mkpath(appsPath);
    QVERIFY(QDir(appsPath).exists());

    QStringList files;
    files << QStringLiteral("file1") << QStringLiteral("file2");
    const QString xdgDatahome = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation) + QLatin1Char('/') + folderName;
    for (const QString &file : qAsConst(files)) {
        QFile fooFile(QLatin1String(MIGRATION_DATA_DIR) + QLatin1Char('/') + file);
        QVERIFY(fooFile.exists());
        const QString storedConfigFilePath = appsPath + QLatin1Char('/') + file;
        QVERIFY(QFile::copy(fooFile.fileName(), storedConfigFilePath));

        const QString xdgFile = xdgDatahome + file;
        QVERIFY(!QFile::exists(xdgFile));
    }

    //SubFolder.
    const QString subFolder = QStringLiteral("foo/folder1/subfolder/");
    const QString appsPathSubfolder = kdehome + QLatin1Char('/') + QLatin1String("share/apps/") + subFolder;
    QDir().mkpath(appsPathSubfolder);
    QVERIFY(QDir(appsPathSubfolder).exists());
    const QString xdgDatahomeSubfolder = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation) + QLatin1Char('/') + subFolder;
    for (const QString &file : qAsConst(files)) {
        QFile fooFile(QLatin1String(MIGRATION_DATA_DIR) + QLatin1Char('/') + file);
        QVERIFY(fooFile.exists());
        const QString storedConfigFilePath = appsPathSubfolder + QLatin1Char('/') + file;
        QVERIFY(QFile::copy(fooFile.fileName(), storedConfigFilePath));

        const QString xdgFile = xdgDatahomeSubfolder + file;
        QVERIFY(!QFile::exists(xdgFile));
    }

    MigrateApplicationFiles migrate;
    migrate.setConfigFileName(QStringLiteral("foorc"));

    MigrateFileInfo info;
    info.setFolder(true);
    info.setPath(folderName);
    info.setType(QStringLiteral("data"));
    info.setVersion(2);
    migrate.insertMigrateInfo(info);

    QVERIFY(migrate.checkIfNecessary());
    migrate.setCurrentConfigVersion(1);

    QVERIFY(migrate.start());
    for (const QString &file : qAsConst(files)) {
        QVERIFY(QFile(xdgDatahome + file).exists());
        QVERIFY(QFile(xdgDatahomeSubfolder + file).exists());
    }
}

void MigrateApplicationFilesTest::shouldNotMigrateIfAlreadyDone()
{
    QTemporaryDir kdehomeDir;
    QVERIFY(kdehomeDir.isValid());
    const QString kdehome = kdehomeDir.path();
    qputenv("KDEHOME", QFile::encodeName(kdehome));

    //Generate kde4 apps dir
    const QString folderName = QStringLiteral("foo/");
    const QString appsPath = kdehome + QLatin1Char('/') + QLatin1String("share/apps/") + folderName;
    QDir().mkpath(appsPath);
    QVERIFY(QDir(appsPath).exists());

    const QString xdgDatahome = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation) + QLatin1Char('/') + folderName;

    QStringList files;
    files << QStringLiteral("file1") << QStringLiteral("file2");
    for (const QString &file : qAsConst(files)) {
        QFile fooFile(QLatin1String(MIGRATION_DATA_DIR) + QLatin1Char('/') + file);
        QVERIFY(fooFile.exists());
        const QString storedConfigFilePath = appsPath + QLatin1Char('/') + file;
        QVERIFY(QFile::copy(fooFile.fileName(), storedConfigFilePath));

        const QString xdgFile = xdgDatahome + file;
        QVERIFY(!QFile::exists(xdgFile));
    }
    MigrateApplicationFiles migrate;
    migrate.setConfigFileName(QStringLiteral("foorc"));

    MigrateFileInfo info;
    info.setPath(folderName + QStringLiteral("file1"));
    info.setType(QStringLiteral("data"));
    info.setVersion(2);
    migrate.insertMigrateInfo(info);

    MigrateFileInfo info2;
    info2.setPath(folderName + QStringLiteral("file2"));
    info2.setType(QStringLiteral("data"));
    info2.setVersion(2);
    migrate.insertMigrateInfo(info2);

    QVERIFY(migrate.checkIfNecessary());
    //We have a current version == 3 => don't migrate old info.
    migrate.setCurrentConfigVersion(3);
    QVERIFY(migrate.start());
    for (const QString &file : qAsConst(files)) {
        QVERIFY(!QFile(xdgDatahome + file).exists());
    }
}

void MigrateApplicationFilesTest::shouldMigrateFiles()
{
    QTemporaryDir kdehomeDir;
    QVERIFY(kdehomeDir.isValid());
    const QString kdehome = kdehomeDir.path();
    qputenv("KDEHOME", QFile::encodeName(kdehome));

    //Generate kde4 apps dir
    const QString folderName = QStringLiteral("foo/");
    const QString appsPath = kdehome + QLatin1Char('/') + QLatin1String("share/apps/") + folderName;
    QDir().mkpath(appsPath);
    QVERIFY(QDir(appsPath).exists());

    const QString xdgDatahome = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation) + QLatin1Char('/') + folderName;

    QStringList files;
    files << QStringLiteral("file1") << QStringLiteral("file2");
    for (const QString &file : qAsConst(files)) {
        QFile fooFile(QLatin1String(MIGRATION_DATA_DIR) + QLatin1Char('/') + file);
        QVERIFY(fooFile.exists());
        const QString storedConfigFilePath = appsPath + QLatin1Char('/') + file;
        //qDebug()<<" storedConfigFilePath"<<storedConfigFilePath;
        QVERIFY(QFile::copy(fooFile.fileName(), storedConfigFilePath));

        const QString xdgFile = xdgDatahome + file;
        QVERIFY(!QFile::exists(xdgFile));
    }
    MigrateApplicationFiles migrate;
    migrate.setConfigFileName(QStringLiteral("foorc"));

    MigrateFileInfo info;
    info.setPath(folderName + QStringLiteral("file1"));
    info.setType(QStringLiteral("data"));
    migrate.insertMigrateInfo(info);

    MigrateFileInfo info2;
    info2.setPath(folderName + QStringLiteral("file2"));
    info2.setType(QStringLiteral("data"));
    migrate.insertMigrateInfo(info2);

    QVERIFY(migrate.checkIfNecessary());
    QVERIFY(migrate.start());
    for (const QString &file : qAsConst(files)) {
        QVERIFY(QFile(xdgDatahome + file).exists());
    }
}

void MigrateApplicationFilesTest::shouldMigrateFilesWithPattern()
{
    QTemporaryDir kdehomeDir;
    QVERIFY(kdehomeDir.isValid());
    const QString kdehome = kdehomeDir.path();
    qputenv("KDEHOME", QFile::encodeName(kdehome));

    //Generate kde4 apps dir
    const QString folderName = QStringLiteral("foo/");
    const QString appsPath = kdehome + QLatin1Char('/') + QLatin1String("share/apps/") + folderName;
    QDir().mkpath(appsPath);
    QVERIFY(QDir(appsPath).exists());
    const QString xdgDatahome = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation) + QLatin1Char('/') + folderName;

    //Copy files.
    QStringList files;
    QStringList filesMustBeMigrated;
    filesMustBeMigrated << QStringLiteral("text2.txt") << QStringLiteral("text.txt");
    QStringList filesMustNotBeMigrated;
    filesMustNotBeMigrated << QStringLiteral("file1") << QStringLiteral("file2");

    files << filesMustBeMigrated << filesMustNotBeMigrated;
    for (const QString &file : qAsConst(files)) {
        QFile fooFile(QLatin1String(MIGRATION_DATA_DIR) + QLatin1Char('/') + file);
        QVERIFY(fooFile.exists());
        const QString storedConfigFilePath = appsPath + QLatin1Char('/') + file;
        //qDebug()<<" storedConfigFilePath"<<storedConfigFilePath;
        QVERIFY(QFile::copy(fooFile.fileName(), storedConfigFilePath));

        const QString xdgFile = xdgDatahome + file;
        QVERIFY(!QFile::exists(xdgFile));
    }

    MigrateApplicationFiles migrate;
    migrate.setConfigFileName(QStringLiteral("foorc"));

    MigrateFileInfo info;
    info.setPath(folderName);
    info.setType(QStringLiteral("data"));
    info.setFolder(false);
    info.setFilePatterns(QStringList() << QStringLiteral("*.txt"));
    migrate.insertMigrateInfo(info);

    QVERIFY(migrate.checkIfNecessary());
    QVERIFY(migrate.start());
    for (const QString &file : qAsConst(filesMustBeMigrated)) {
        QVERIFY(QFile(xdgDatahome + file).exists());
    }
    for (const QString &file : qAsConst(filesMustNotBeMigrated)) {
        QVERIFY(!QFile(xdgDatahome + file).exists());
    }
}

void MigrateApplicationFilesTest::cleanup()
{
    QStandardPaths::setTestModeEnabled(true);
    const QString applicationHome = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation);
    QDir applicationDir(applicationHome);
    applicationDir.removeRecursively();
    const QString configHome = QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation);
    QDir configDir(configHome);
    configDir.removeRecursively();
}

QTEST_MAIN(MigrateApplicationFilesTest)
