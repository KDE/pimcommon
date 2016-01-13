/*
  Copyright (c) 2016 Montel Laurent <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License, version 2, as
  published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/


#include "genericscriptsmanager.h"
#include "genericscriptaction.h"
#include "pimcommon_debug.h"
#include <QStandardPaths>
#include <QDir>
#include <QJsonParseError>

using namespace PimCommon;

class GenericScriptsManagerInstancePrivate
{
public:
    GenericScriptsManagerInstancePrivate()
        : genericScriptsManager(new GenericScriptsManager)
    {
    }

    ~GenericScriptsManagerInstancePrivate()
    {
        delete genericScriptsManager;
    }

    GenericScriptsManager *genericScriptsManager;
};

Q_GLOBAL_STATIC(GenericScriptsManagerInstancePrivate, sInstance)

class PimCommon::GenericScriptsManagerPrivate
{
public:
    GenericScriptsManagerPrivate()
        : actionCollection(Q_NULLPTR)
    {

    }
    QString scriptPath;
    QVector<PimCommon::GenericScriptAction *> listScriptActions;
    KActionCollection *actionCollection;
};

GenericScriptsManager::GenericScriptsManager(QObject *parent)
    : QObject(parent),
      d(new PimCommon::GenericScriptsManagerPrivate)
{

}

GenericScriptsManager::~GenericScriptsManager()
{
    delete d;
}

GenericScriptsManager *GenericScriptsManager::self()
{
    return sInstance->genericScriptsManager;
}

void GenericScriptsManager::setScriptPath(const QString &path)
{
    d->scriptPath = path;
}

void GenericScriptsManager::setActionCollection(KActionCollection *ac)
{
    d->actionCollection = ac;
}

void GenericScriptsManager::initializeScripts()
{
    if (d->scriptPath.isEmpty()) {
        qCWarning(PIMCOMMON_LOG) << "Script path is not defined";
    } else {
        const QString basedir = d->scriptPath;
        QStringList dirs;
        // first writable locations, e.g. stuff the user has provided
        foreach (const QString &dir, QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation)) {
            dirs.append(dir + basedir);
        }
        QStringList list;
        if (!dirs.isEmpty()) {
            foreach (const QString &dir, dirs) {
                const QStringList fileNames = QDir(dir).entryList(QStringList() << QStringLiteral("*.js"));
                foreach (const QString &file, fileNames) {
                    list.append(dir + QLatin1Char('/') + file);
                }
            }
        }
        //Code based on kate code
        // iterate through the files and read info out of cache or file, no double loading of same scripts
        QSet<QString> unique;
        foreach (const QString &fileName, list) {
            const QString baseName = QFileInfo(fileName).baseName();
            if (unique.contains(baseName))
                continue;
            unique.insert(baseName);
            QFile file(fileName);
            if (!file.open(QIODevice::ReadOnly)) {
                qCDebug(PIMCOMMON_LOG) << "Script parse error: Cannot open file " << fileName;
                continue;
            }

            /**
             * search json header or skip this file
             */
            QByteArray fileContent = file.readAll();
            const int startOfJson = fileContent.indexOf ('{');
            if (startOfJson < 0) {
                qCDebug(PIMCOMMON_LOG) << "Script parse error: Cannot find start of json header at start of file " << fileName;
                continue;
            }

            int endOfJson = fileContent.indexOf("\n};", startOfJson);
            if (endOfJson < 0) { // as fallback, check also mac os line ending
                endOfJson = fileContent.indexOf("\r};", startOfJson);
            }
            if (endOfJson < 0) {
                qCDebug(PIMCOMMON_LOG) << "Script parse error: Cannot find end of json header at start of file " << fileName;
                continue;
            }
            endOfJson += 2; //we want the end including the } but not the ;

            /**
             * parse json header or skip this file
             */
            QJsonParseError error;
            const QJsonDocument metaInfo (QJsonDocument::fromJson(fileContent.mid(startOfJson, endOfJson-startOfJson), &error));
            if (error.error || !metaInfo.isObject()) {
                qCDebug(PIMCOMMON_LOG) << "Script parse error: Cannot parse json header at start of file " << fileName
                                       << error.errorString() << endOfJson << fileContent.mid(endOfJson-25, 25).replace('\n', ' ');
                continue;
            }
        }
        //TODO load all scripts.

    }
    //TODO
}

QVector<PimCommon::GenericScriptAction *> GenericScriptsManager::listScriptActions() const
{
    return d->listScriptActions;
}
