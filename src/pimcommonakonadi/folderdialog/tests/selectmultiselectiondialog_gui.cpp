/*
  SPDX-FileCopyrightText: 2013-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "pimcommonakonadi_debug.h"

#include "folderdialog/selectmulticollectiondialog.h"
#include <KMime/Message>
#include <QApplication>
#include <QCommandLineParser>
#include <QStandardPaths>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QStandardPaths::setTestModeEnabled(true);
    QCommandLineParser parser;
    parser.addVersionOption();
    parser.addHelpOption();
    parser.process(app);
    auto dialog = new PimCommon::SelectMultiCollectionDialog(KMime::Message::mimeType());
    dialog->exec();
    delete dialog;
    return 0;
}
