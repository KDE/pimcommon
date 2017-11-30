/*
  Copyright (c) 2015-2017 Montel Laurent <montel@kde.org>

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

#include "customtoolswidgetng.h"
#include "customtoolsplugin.h"
#include "customtoolspluginmanager.h"
#include "customtoolsviewinterface.h"

#include <KToggleAction>

#include <QHBoxLayout>
#include <QStackedWidget>

using namespace PimCommon;

class PimCommon::CustomToolsWidgetNgPrivate
{
public:
    CustomToolsWidgetNgPrivate()
    {
    }

    QStackedWidget *mStackedWidget = nullptr;
    QList<PimCommon::CustomToolsViewInterface *> mListInterfaceView;
};

CustomToolsWidgetNg::CustomToolsWidgetNg(KActionCollection *ac, QWidget *parent)
    : QWidget(parent)
    , d(new PimCommon::CustomToolsWidgetNgPrivate)
{
    QHBoxLayout *lay = new QHBoxLayout(this);
    d->mStackedWidget = new QStackedWidget;
    d->mStackedWidget->setObjectName(QStringLiteral("stackedwidget"));
    lay->addWidget(d->mStackedWidget);
    initializeView(ac);
    hide();
}

CustomToolsWidgetNg::~CustomToolsWidgetNg()
{
    delete d;
}

void CustomToolsWidgetNg::initializeView(KActionCollection *ac)
{
    const QVector<CustomToolsPlugin *> localPluginsList = PimCommon::CustomToolsPluginManager::self()->pluginsList();
    for (CustomToolsPlugin *plugin : localPluginsList) {
        PimCommon::CustomToolsViewInterface *localCreateView = plugin->createView(ac, this);
        d->mListInterfaceView.append(localCreateView);
        d->mStackedWidget->addWidget(localCreateView);
    }
}

void CustomToolsWidgetNg::slotToolsWasClosed()
{
    for (PimCommon::CustomToolsViewInterface *interface : qAsConst(d->mListInterfaceView)) {
        interface->action()->setChecked(false);
    }
    hide();
}

void CustomToolsWidgetNg::slotActivateView(QWidget *w)
{
    if (w) {
        d->mStackedWidget->setCurrentWidget(w);
        setVisible(true);
        for (PimCommon::CustomToolsViewInterface *interface : qAsConst(d->mListInterfaceView)) {
            if (interface != w) {
                interface->action()->setChecked(false);
            }
        }
        Q_EMIT toolActivated();
    } else {
        setVisible(false);
        slotToolsWasClosed();
    }
}

QList<KToggleAction *> CustomToolsWidgetNg::actionList() const
{
    QList<KToggleAction *> lstActions;
    lstActions.reserve(d->mListInterfaceView.count());
    for (PimCommon::CustomToolsViewInterface *interface : qAsConst(d->mListInterfaceView)) {
        lstActions << interface->action();
    }
    return lstActions;
}

void CustomToolsWidgetNg::setText(const QString &text)
{
    if (isVisible()) {
        for (PimCommon::CustomToolsViewInterface *interface : qAsConst(d->mListInterfaceView)) {
            if (interface == d->mStackedWidget->currentWidget()) {
                interface->setText(text);
                break;
            }
        }
    }
}
