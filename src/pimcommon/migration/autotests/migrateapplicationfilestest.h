/*
  SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#ifndef MIGRATEAPPLICATIONFILESTEST_H
#define MIGRATEAPPLICATIONFILESTEST_H

#include <QObject>

class MigrateApplicationFilesTest : public QObject
{
    Q_OBJECT
public:
    explicit MigrateApplicationFilesTest(QObject *parent = nullptr);
    ~MigrateApplicationFilesTest();
private Q_SLOTS:
    void initTestCase();
    void shouldHaveDefaultValue();
    void shouldVerifyIfCheckIsNecessary();
    void shouldNotMigrateIfKdehomeDoNotExist();
    void shouldMigrateIfKde4HomeDirExist();
    void shouldMigrateFolders();
    void shouldNotMigrateFoldersIfAlreadyDone();
    void shouldMigrateFoldersWithSubFolders();

    void shouldMigrateFiles();
    void shouldMigrateFilesWithPattern();
    void cleanup();
    void shouldNotMigrateIfAlreadyDone();
};

#endif // MIGRATEAPPLICATIONFILESTEST_H
