/*
  SPDX-FileCopyrightText: 2013-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include <QWidget>
#include <QVBoxLayout>

#include <QApplication>
#include <QCommandLineParser>

#include "../spellchecklineedit.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QCommandLineParser parser;
    parser.addVersionOption();
    parser.addHelpOption();
    parser.process(app);

    auto w = new QWidget;
    auto vbox = new QVBoxLayout(w);

    auto spellCheckLineEdit = new PimCommon::SpellCheckLineEdit(w, QStringLiteral("testspecklineeditrc"));
    vbox->addWidget(spellCheckLineEdit);
    vbox->addStretch();

    w->resize(400, 400);
    w->show();

    return app.exec();
}
