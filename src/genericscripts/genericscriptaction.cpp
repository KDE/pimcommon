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

#include "genericscriptaction.h"
#include <KActionCollection>

using namespace PimCommon;

class PimCommon::GenericScriptActionPrivate
{
public:
    GenericScriptActionPrivate(GenericScriptAction *qq, const QJsonObject &action)
        : q(qq)
    {
        initializeAction(action);
    }
    void initializeAction(const QJsonObject &action);
    GenericScriptAction *q;
};

void GenericScriptActionPrivate::initializeAction(const QJsonObject &action)
{
    //TODO
}

GenericScriptAction::GenericScriptAction(const QJsonObject &action, KActionCollection *ac, QObject *parent)
    : QAction(parent),
      d(new PimCommon::GenericScriptActionPrivate(this, action))
{
    //ac->addAction(, this);
    connect(this, &QAction::triggered, this, &GenericScriptAction::slotActivateAction);
}

GenericScriptAction::~GenericScriptAction()
{
    delete d;
}

void GenericScriptAction::slotActivateAction()
{
    Q_EMIT activateAction(this);
}

void GenericScriptAction::exec()
{

    //TODO
}

