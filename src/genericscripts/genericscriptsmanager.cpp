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

    }
    //TODO
}

QVector<PimCommon::GenericScriptAction *> GenericScriptsManager::listScriptActions() const
{
    return d->listScriptActions;
}
