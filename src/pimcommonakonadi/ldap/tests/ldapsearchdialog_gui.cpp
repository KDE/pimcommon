/*
  SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include <QApplication>
#include <QCommandLineParser>
#include <QStandardPaths>

#include "ldap/ldapsearchdialog.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QCommandLineParser parser;
    // We can't use it otherwise we need to call kbuilsyscoca in test mode too.
    // QStandardPaths::setTestModeEnabled(true);
    parser.addVersionOption();
    parser.addHelpOption();
    parser.process(app);

    PimCommon::LdapSearchDialog dlg;
    dlg.exec();
    return app.exec();
}
