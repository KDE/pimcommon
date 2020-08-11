/*
    This file is part of libkdepim.

    SPDX-FileCopyrightText: 2004 Daniel Molkentin <danimo@klaralvdalens-datakonsult.se>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include <QWidget>
#include <QVBoxLayout>

#include <PimCommonAkonadi/AddresseeLineEdit>

#include <QApplication>
#include <QCommandLineParser>
#include <QStandardPaths>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QStandardPaths::setTestModeEnabled(true);
    QCommandLineParser parser;
    parser.addVersionOption();
    parser.addHelpOption();
    parser.process(app);

    QWidget *w = new QWidget;
    QVBoxLayout *vbox = new QVBoxLayout(w);

    PimCommon::AddresseeLineEdit *kale1 = new PimCommon::AddresseeLineEdit(nullptr);
    vbox->addWidget(kale1);
    PimCommon::AddresseeLineEdit *kale2 = new PimCommon::AddresseeLineEdit(nullptr);
    vbox->addWidget(kale2);
    vbox->addStretch();

    w->resize(400, 400);
    w->show();

    return app.exec();
}
