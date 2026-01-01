/*
  SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "customtoolswidgetng.h"
using namespace Qt::Literals::StringLiterals;

#include "customtoolsplugin.h"
#include "customtoolsviewinterface.h"

#include <KToggleAction>

#include <QHBoxLayout>
#include <QStackedWidget>

using namespace PimCommon;

class PimCommon::CustomToolsWidgetNgPrivate
{
public:
    CustomToolsWidgetNgPrivate() = default;

    QStackedWidget *mStackedWidget = nullptr;
    QList<PimCommon::CustomToolsViewInterface *> mListInterfaceView;
};

CustomToolsWidgetNg::CustomToolsWidgetNg(QWidget *parent)
    : QWidget(parent)
    , d(new PimCommon::CustomToolsWidgetNgPrivate)
{
    auto lay = new QHBoxLayout(this);
    lay->setContentsMargins({});
    d->mStackedWidget = new QStackedWidget;
    d->mStackedWidget->setObjectName("stackedwidget"_L1);
    lay->addWidget(d->mStackedWidget);
    hide();
}

CustomToolsWidgetNg::~CustomToolsWidgetNg() = default;

void CustomToolsWidgetNg::addCustomToolViewInterface(PimCommon::CustomToolsViewInterface *plugin)
{
    d->mListInterfaceView.append(plugin);
    d->mStackedWidget->addWidget(plugin);
}

void CustomToolsWidgetNg::initializeView(KActionCollection *ac, const QList<CustomToolsPlugin *> &localPluginsList)
{
    for (CustomToolsPlugin *plugin : localPluginsList) {
        PimCommon::CustomToolsViewInterface *localCreateView = plugin->createView(ac, this);
        d->mListInterfaceView.append(localCreateView);
        d->mStackedWidget->addWidget(localCreateView);
    }
}

void CustomToolsWidgetNg::slotToolsWasClosed()
{
    for (const PimCommon::CustomToolsViewInterface *interface : std::as_const(d->mListInterfaceView)) {
        interface->action()->setChecked(false);
    }
    hide();
}

void CustomToolsWidgetNg::slotActivateView(QWidget *w)
{
    if (w) {
        d->mStackedWidget->setCurrentWidget(w);
        setVisible(true);
        for (const PimCommon::CustomToolsViewInterface *interface : std::as_const(d->mListInterfaceView)) {
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
    for (const PimCommon::CustomToolsViewInterface *interface : std::as_const(d->mListInterfaceView)) {
        lstActions << interface->action();
    }
    return lstActions;
}

void CustomToolsWidgetNg::setText(const QString &text)
{
    if (isVisible()) {
        auto currentWidget = d->mStackedWidget->currentWidget();
        auto it = std::find_if(d->mListInterfaceView.cbegin(), d->mListInterfaceView.cend(), [currentWidget](auto interface) {
            return interface == currentWidget;
        });
        if (it != d->mListInterfaceView.cend()) {
            (*it)->setText(text);
        }
    }
}

#include "moc_customtoolswidgetng.cpp"
