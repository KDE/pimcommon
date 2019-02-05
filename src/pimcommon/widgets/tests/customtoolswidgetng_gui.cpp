/*
  Copyright (c) 2015-2019 Montel Laurent <montel@kde.org>

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
    QVBoxLayout *lay = new QVBoxLayout(this);

    QToolBar *menu = new QToolBar(this);
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

    CustomToolWidgetNgTest *w = new CustomToolWidgetNgTest();
    w->resize(800, 200);
    w->show();
    const int ret = app.exec();
    delete w;
    return ret;
}
