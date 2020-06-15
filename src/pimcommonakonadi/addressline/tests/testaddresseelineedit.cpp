/*
    This file is part of libkdepim.

    Copyright (c) 2004 Daniel Molkentin <danimo@klaralvdalens-datakonsult.se>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
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
