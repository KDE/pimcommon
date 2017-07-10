/*
  Copyright (c) 2017 Montel Laurent <montel@kde.org>

  based on lineedit in kpassworddialog.cpp

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


#include "lineeditpassword.h"
#include <KLocalizedString>
#include <QIcon>
#include <QAction>
#include <QHBoxLayout>
#include <QLineEdit>

using namespace PimCommon;

class PimCommon::LineEditPassword::LineEditPasswordPrivate
{
public:
    LineEditPasswordPrivate()
    {

    }
    QLineEdit *mPasswordLineEdit = nullptr;
    QAction *mToggleEchoModeAction = nullptr;
    bool mIsToggleEchoModeAvailable = true;
};

LineEditPassword::LineEditPassword(QWidget *parent)
    : QWidget(parent)
    , d(new LineEditPasswordPrivate)
{
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setMargin(0);
    d->mPasswordLineEdit = new QLineEdit(this);
    d->mPasswordLineEdit->setObjectName(QStringLiteral("passwordlineedit"));
    d->mPasswordLineEdit->setEchoMode(QLineEdit::Password);
    mainLayout->addWidget(d->mPasswordLineEdit);
    initialize();
}

LineEditPassword::~LineEditPassword()
{
    delete d;
}

void LineEditPassword::initialize()
{
    QIcon visibilityIcon = QIcon::fromTheme(QStringLiteral("visibility"), QIcon(QStringLiteral(":/icons/visibility.svg")));
    d->mToggleEchoModeAction = d->mPasswordLineEdit->addAction(visibilityIcon, QLineEdit::TrailingPosition);
    d->mToggleEchoModeAction->setObjectName(QStringLiteral("visibilityAction"));
    d->mToggleEchoModeAction->setVisible(false);
    d->mToggleEchoModeAction->setToolTip(i18n("Change the visibility of the password"));

    connect(d->mToggleEchoModeAction, &QAction::triggered, this, &LineEditPassword::toggleEchoMode);

    connect(d->mPasswordLineEdit, &QLineEdit::textChanged, this, &LineEditPassword::showToggleEchoModeAction);
}

void LineEditPassword::toggleEchoMode()
{
    if (d->mPasswordLineEdit->echoMode() == QLineEdit::Password) {
        d->mPasswordLineEdit->setEchoMode(QLineEdit::Normal);
        d->mToggleEchoModeAction->setIcon(QIcon::fromTheme(QStringLiteral("hint"), QIcon(QStringLiteral(":/icons/hint.svg"))));
    } else if (d->mPasswordLineEdit->echoMode() == QLineEdit::Normal) {
        d->mPasswordLineEdit->setEchoMode(QLineEdit::Password);
        d->mToggleEchoModeAction->setIcon(QIcon::fromTheme(QStringLiteral("visibility"), QIcon(QStringLiteral(":/icons/visibility.svg"))));
    }
}

void LineEditPassword::setPassword(const QString &p)
{
    d->mIsToggleEchoModeAvailable = p.isEmpty();
    d->mPasswordLineEdit->setText(p);
}

QString LineEditPassword::password() const
{
    return d->mPasswordLineEdit->text();
}

void LineEditPassword::showToggleEchoModeAction(const QString &text)
{
    d->mToggleEchoModeAction->setVisible(d->mIsToggleEchoModeAvailable && (d->mPasswordLineEdit->echoMode() == QLineEdit::Normal || !text.isEmpty()));
}

QLineEdit *LineEditPassword::passwordLineEdit() const
{
    return d->mPasswordLineEdit;
}

QAction *LineEditPassword::toggleEchoModeAction() const
{
    return d->mToggleEchoModeAction;
}
