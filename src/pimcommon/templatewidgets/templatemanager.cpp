/*
  SPDX-FileCopyrightText: 2013-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "templatemanager.h"
#include "pimcommon_debug.h"
#include "templatewidgets/templatelistwidget.h"

#include <KDirWatch>

#include <KConfig>
#include <KConfigGroup>

#include <QDirIterator>
#include <QStandardPaths>

using namespace PimCommon;

class PimCommon::TemplateManagerPrivate
{
public:
    QStringList mTemplatesDirectories;
    PimCommon::TemplateListWidget *mTemplateListWidget = nullptr;
    KDirWatch *mDirWatch = nullptr;
};

TemplateManager::TemplateManager(const QString &relativeTemplateDir, PimCommon::TemplateListWidget *templateListWidget)
    : QObject(templateListWidget)
    , d(new PimCommon::TemplateManagerPrivate)
{
    d->mTemplateListWidget = templateListWidget;
    d->mDirWatch = new KDirWatch(this);
    initTemplatesDirectories(relativeTemplateDir);

    connect(d->mDirWatch, &KDirWatch::dirty, this, &TemplateManager::slotDirectoryChanged);
    loadTemplates(true);
}

TemplateManager::~TemplateManager() = default;

void TemplateManager::slotDirectoryChanged()
{
    d->mTemplateListWidget->loadTemplates();
    loadTemplates();
}

void TemplateManager::initTemplatesDirectories(const QString &templatesRelativePath)
{
    if (!templatesRelativePath.isEmpty()) {
        d->mTemplatesDirectories = QStandardPaths::locateAll(QStandardPaths::GenericDataLocation, templatesRelativePath, QStandardPaths::LocateDirectory);
        if (d->mTemplatesDirectories.count() < 2) {
            // Make sure to add local directory
            const QString localDirectory = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation) + QLatin1Char('/') + templatesRelativePath;
            if (!d->mTemplatesDirectories.contains(localDirectory)) {
                d->mTemplatesDirectories.append(localDirectory);
            }
        }
    }
}

void TemplateManager::loadTemplates(bool init)
{
    if (!init) {
        if (!d->mTemplatesDirectories.isEmpty()) {
            for (const QString &directory : std::as_const(d->mTemplatesDirectories)) {
                d->mDirWatch->removeDir(directory);
            }
        } else {
            return;
        }
    }

    for (const QString &directory : std::as_const(d->mTemplatesDirectories)) {
        QDirIterator dirIt(directory, QStringList(), QDir::AllDirs | QDir::NoDotAndDotDot);
        while (dirIt.hasNext()) {
            dirIt.next();
            TemplateInfo info = loadTemplate(dirIt.filePath(), QStringLiteral("template.desktop"));
            if (info.isValid()) {
                d->mTemplateListWidget->addDefaultTemplate(info.name, info.script);
            }
        }
        d->mDirWatch->addDir(directory);
    }
    d->mDirWatch->startScan();
}

TemplateInfo TemplateManager::loadTemplate(const QString &themePath, const QString &defaultDesktopFileName)
{
    TemplateInfo info;
    const QString themeInfoFile = themePath + QLatin1Char('/') + defaultDesktopFileName;
    KConfig config(themeInfoFile);
    KConfigGroup group(&config, QStringLiteral("Desktop Entry"));

    info.name = group.readEntry("Name", QString());
    const QString filename = group.readEntry("FileName", QString());
    if (!filename.isEmpty()) {
        QFile file(themePath + QLatin1Char('/') + filename);
        if (file.exists()) {
            if (file.open(QIODevice::ReadOnly)) {
                info.script = QString::fromUtf8(file.readAll());
            }
        }
    }
    return info;
}

void TemplateInfo::debug() const
{
    qCDebug(PIMCOMMON_LOG) << " name :" << name << " script :" << script;
}
