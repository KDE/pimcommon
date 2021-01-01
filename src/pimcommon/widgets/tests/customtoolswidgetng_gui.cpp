/*
  SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "customtoolswidgetng_gui.h"
#include "customtools/customtoolswidgetng.h"
#include "customtools/customtoolspluginmanager.h"
#include <QStandardPaths>
#include <KToggleAction>

#include <QVBoxLayout>
#include <QApplication>
#include <QCommandLineParser>
#include <QToolBar>

#include <KXmlGui/kactioncollection.h>

CustomToolWidgetNgTest::CustomToolWidgetNgTest(QWidget *parent)
    : QWidget(parent)
{
    auto *lay = new QVBoxLayout(this);

    auto *menu = new QToolBar(this);
    lay->addWidget(menu);

    mCustomTools = new PimCommon::CustomToolsWidgetNg(this);
    mCustomTools->initializeView(new KActionCollection(this), PimCommon::CustomToolsPluginManager::self()->pluginsList());
    const QList<KToggleAction *> lst = mCustomTools->actionList();
    for (KToggleAction *act : lst) {
        menu->addAction(act);
    }

    lay->addWidget(mCustomTools);
}

CustomToolWidgetNgTest::~CustomToolWidgetNgTest()
{
}

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QStandardPaths::setTestModeEnabled(true);
    QCommandLineParser parser;
    parser.addVersionOption();
    parser.addHelpOption();
    parser.process(app);

    auto *w = new CustomToolWidgetNgTest();
    w->resize(800, 200);
    w->show();
    const int ret = app.exec();
    delete w;
    return ret;
}
