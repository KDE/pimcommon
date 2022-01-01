/*
  SPDX-FileCopyrightText: 2015-2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "migratefileinfotest.h"
#include "../migratefileinfo.h"
#include <QTest>
using namespace PimCommon;
MigrateFileInfoTest::MigrateFileInfoTest(QObject *parent)
    : QObject(parent)
{
}

MigrateFileInfoTest::~MigrateFileInfoTest() = default;

void MigrateFileInfoTest::shouldHaveDefaultValue()
{
    MigrateFileInfo info;
    QVERIFY(!info.folder());
    QVERIFY(info.path().isEmpty());
    QVERIFY(info.type().isEmpty());
    QVERIFY(info.filePatterns().isEmpty());
    QCOMPARE(info.version(), -1);
}

void MigrateFileInfoTest::shouldAssignValue()
{
    MigrateFileInfo info;
    bool isFolder = false;
    info.setFolder(isFolder);
    QCOMPARE(info.folder(), isFolder);
    isFolder = true;
    info.setFolder(isFolder);
    QCOMPARE(info.folder(), isFolder);
    isFolder = false;
    info.setFolder(isFolder);
    QCOMPARE(info.folder(), isFolder);

    QString path;
    info.setPath(path);
    QCOMPARE(info.path(), path);
    path = QStringLiteral("foo");
    info.setPath(path);
    QCOMPARE(info.path(), path);
    path.clear();
    info.setPath(path);
    QCOMPARE(info.path(), path);

    QString type;
    info.setType(type);
    QCOMPARE(info.type(), type);
    type = QStringLiteral("foo");
    info.setType(type);
    QCOMPARE(info.type(), type);
    type.clear();
    info.setType(type);
    QCOMPARE(info.type(), type);

    int version = -1;
    info.setVersion(version);
    QCOMPARE(info.version(), version);
    version = 6;
    info.setVersion(version);
    QCOMPARE(info.version(), version);

    QStringList pattern;
    info.setFilePatterns(pattern);
    QCOMPARE(info.filePatterns(), pattern);
    pattern = QStringList() << QStringLiteral("foo");
    info.setFilePatterns(pattern);
    QCOMPARE(info.filePatterns(), pattern);
    pattern.clear();
    info.setFilePatterns(pattern);
    QCOMPARE(info.filePatterns(), pattern);
}

void MigrateFileInfoTest::shouldBeEmpty()
{
    MigrateFileInfo info;
    QVERIFY(!info.isValid());
    info.setFolder(true);
    QVERIFY(!info.isValid());

    const QString type = QStringLiteral("foo");
    info.setType(type);
    QVERIFY(!info.isValid());

    QString path = QStringLiteral("foo");
    info.setPath(path);
    QVERIFY(info.isValid());

    path.clear();
    info.setPath(path);
    QVERIFY(!info.isValid());
}

QTEST_MAIN(MigrateFileInfoTest)
