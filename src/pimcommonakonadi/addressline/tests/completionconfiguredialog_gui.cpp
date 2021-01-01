/*
  SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include <QApplication>
#include <QCommandLineParser>
#include <QStandardPaths>

#include <addressline/completionconfiguredialog/completionconfiguredialog.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QCommandLineParser parser;
    QStandardPaths::setTestModeEnabled(true);
    parser.addVersionOption();
    parser.addHelpOption();
    parser.process(app);

    PimCommon::CompletionConfigureDialog dlg;
    dlg.show();

    return app.exec();
}
