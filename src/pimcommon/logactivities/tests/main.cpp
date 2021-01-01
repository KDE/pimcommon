/*
   SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include <QStandardPaths>
#include <QApplication>
#include <QCommandLineParser>
#include "logactivitiesmainwidget.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QStandardPaths::setTestModeEnabled(true);
    QCommandLineParser parser;
    parser.addVersionOption();
    parser.addHelpOption();

    parser.process(app);

    auto *w = new LogActivitiesMainWidget;
    w->show();
    app.exec();
    return 0;
}
